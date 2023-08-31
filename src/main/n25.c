#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h> //RAW IP lvl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096
#define SERVER_IP "127.0.0.1"
#define SPORT 8888
#define PORT 7777

int
main ()
{
  char buffer[BUFF_SIZE];
  char msg[] = "HI 1245251!";

  int raw_socket;
  struct sockaddr_in serv;
  struct iphdr *ipheader = (struct iphdr *)buffer;
  struct udphdr *udpheader = (struct udphdr *)(buffer + sizeof (struct iphdr));

  raw_socket = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
  if (raw_socket == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  int enabled = 1;
  const int *val = &enabled;
  if (setsockopt (raw_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof (enabled))
      < 0)
    {
      perror ("setsockopt");
      return 1;
    }

  memset (&serv, 0, sizeof (serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons (PORT);
  inet_pton (AF_INET, SERVER_IP, &(serv.sin_addr));

  memset (buffer, 0, 4096);

  ipheader->ihl = 5;
  ipheader->version = 4;
  ipheader->tos = 0;
  ipheader->tot_len
      = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen (msg);
  ipheader->id = htons (1);
  ipheader->frag_off = 0;
  ipheader->ttl = 254;
  ipheader->protocol = IPPROTO_UDP;
  ipheader->check = 0;
  ipheader->saddr = inet_addr (SERVER_IP);
  ipheader->daddr = serv.sin_addr.s_addr;

  udpheader->source = htons (SPORT);
  udpheader->dest = htons (PORT);
  udpheader->len = htons (sizeof (struct udphdr) + strlen (msg));
  udpheader->check = 0;

  memcpy (buffer + sizeof (struct iphdr) + sizeof (struct udphdr), msg,
          strlen (msg));

  if (sendto (raw_socket, buffer, ipheader->tot_len, 0,
              (struct sockaddr *)&serv, sizeof (serv))
      < 0)
    {
      perror ("Error accepting connection\n");
      close (raw_socket);
      exit (EXIT_FAILURE);
    }

  memset (buffer, 0, 4096);

  while (1)
    {
      int received_bytes
          = recvfrom (raw_socket, buffer, BUFF_SIZE, 0, NULL, NULL);
      if (received_bytes == -1)
        {
          perror ("Error accepting connection\n");
          close (raw_socket);
          exit (EXIT_FAILURE);
        }

      struct iphdr *received_iph = (struct iphdr *)buffer;
      struct udphdr *received_udph
          = (struct udphdr *)(buffer + sizeof (struct iphdr));

      if (ntohs (received_udph->dest) == 8888)
        {
          printf ("src-ip = %s \ndst-ip = %s",
                  inet_ntoa (*(struct in_addr *)&received_iph->saddr),
                  inet_ntoa (*(struct in_addr *)&received_iph->daddr));

          printf ("\nsrc-port = %d \ndst-port = %d \nlenght = %d \ncheck = %d "
                  "\nmessage:%s\n\n",
                  ntohs (received_udph->source), ntohs (received_udph->dest),
                  ntohs (received_udph->len), ntohs (received_udph->check),
                  (buffer + sizeof (struct udphdr) + sizeof (struct iphdr)));

          break;
        }
    }

  close (raw_socket);
  return 0;
}
