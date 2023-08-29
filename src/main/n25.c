#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h> //RAW IP lvl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFF_SIZE 8192
#define SERVER_IP "127.0.0.2"
#define SPORT 8888
#define PORT 7777

char SMAC[6] = { 0x08, 0x00, 0x27, 0x93, 0x07, 0xba };
// char SMAC[6] = {0x52, 0x54, 0x00, 0x12, 0x35, 0x02};
// char SMAC[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// char DMAC[6] = {0xFF, 0x02, 0x00, 0x00, 0x00, 0x00};
int DMAC[6] = { 52, 54, 00, 12, 35, 02 };

static int
IpChecksum (char *ip_hdr_ptr)
{
  short *ptr = (short *)ip_hdr_ptr;

  for (short *i = (short *)ip_hdr_ptr; i < (short *)ip_hdr_ptr + 10; i++)
    {
      ((struct iphdr *)ip_hdr_ptr)->check += *i;
    }

  int tmp = ((struct iphdr *)ip_hdr_ptr)->check >> 16;
  ((struct iphdr *)ip_hdr_ptr)->check
      = (((struct iphdr *)ip_hdr_ptr)->check & 0xffff) + tmp;
  ((struct iphdr *)ip_hdr_ptr)->check = ~(((struct iphdr *)ip_hdr_ptr)->check);
}

int
main ()
{
  char buffer[BUFF_SIZE];
  char msg[] = "HI 1245251!";

  int raw_socket;
  struct sockaddr_ll serv;
  struct ethhdr *ethhdr = (struct ethhdr *)buffer;
  struct iphdr *ipheader = (struct iphdr *)(buffer + sizeof (struct ethhdr));
  struct udphdr *udpheader
      = (struct udphdr *)(buffer
                          + (sizeof (struct iphdr) + sizeof (struct ethhdr)));

  raw_socket = socket (AF_PACKET, SOCK_RAW, htons (ETH_P_ALL));
  if (raw_socket == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  /*
  int enabled = 1;
  const int *val = &enabled;
  if (setsockopt(raw_socket, IPPROTO_IP, IP_HDRINCL, val, sizeof(enabled)) < 0)
  { perror("setsockopt"); return 1;
  }*/

  memset (&serv, 0, sizeof (serv));
  serv.sll_family = AF_PACKET;
  serv.sll_halen = 6;
  serv.sll_ifindex = 2;
  serv.sll_addr[0] = DMAC[0];
  serv.sll_addr[1] = DMAC[1];
  serv.sll_addr[2] = DMAC[2];
  serv.sll_addr[3] = DMAC[3];
  serv.sll_addr[4] = DMAC[4];
  serv.sll_addr[5] = DMAC[5];

  // strcpy(serv.sll_addr, DMAC);

  memset (buffer, 0, BUFF_SIZE);

  strncpy (ethhdr->h_source, SMAC, 6);
  strncpy (ethhdr->h_dest, DMAC, 6);
  ethhdr->h_proto = htons (ETH_P_IP);

  ipheader->ihl = 5;
  ipheader->version = 4;
  ipheader->tos = 0;
  ipheader->tot_len
      = htons (sizeof (struct iphdr) + sizeof (struct udphdr) + strlen (msg));
  ipheader->id = htons (1);
  ipheader->frag_off = 0;
  ipheader->ttl = 254;
  ipheader->protocol = IPPROTO_UDP;
  ipheader->saddr = inet_addr (SERVER_IP);
  ipheader->daddr = serv.sll_addr;
  IpChecksum (ipheader);

  udpheader->source = htons (SPORT);
  udpheader->dest = htons (PORT);
  udpheader->len = htons (sizeof (struct udphdr) + strlen (msg));
  udpheader->check = 0;

  memcpy (buffer + sizeof (struct ethhdr) + sizeof (struct iphdr)
              + sizeof (struct udphdr),
          msg, strlen (msg));

  if (sendto (raw_socket, buffer,
              sizeof (struct iphdr) + sizeof (struct udphdr)
                  + sizeof (struct ethhdr) + strlen (msg),
              0, (struct sockaddr *)&serv, sizeof (serv))
      < 0)
    {
      perror ("Error accepting connection\n");
      close (raw_socket);
      exit (EXIT_FAILURE);
    }

  memset (buffer, 0, BUFF_SIZE);

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
