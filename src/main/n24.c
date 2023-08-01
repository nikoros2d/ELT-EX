#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXB 100
#define PORT 7777
#define SPORT 8888
#define PATH "/tmp/stream_serv"
#include <linux/udp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int
main (int argc, char *argv[])
{
  char *msg = (char *)malloc (sizeof (struct udphdr) + 20);
  ((struct udphdr *)msg)->source = htons (PORT);
  ((struct udphdr *)msg)->dest = htons (SPORT);
  ((struct udphdr *)msg)->len = htons (sizeof (struct udphdr) + 20);
  ((struct udphdr *)msg)->check = htons (0);
  strcpy (msg + sizeof (struct udphdr), "HELLO?!");
  char hi[MAXB];
  int fd;
  printf ("USE SUDO!!!\n");
  fd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons (PORT);
  serv.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
  socklen_t addrlen = sizeof (serv);
  char *buf = (char *)malloc (sizeof (struct udphdr) + 42);
  if (sendto (fd, (void *)msg, sizeof (struct udphdr) + 20, 0,
              (struct sockaddr *)&serv, addrlen)
      == -1)
    {
      perror ("send");
      exit (EXIT_FAILURE);
    };
  while (1)
    {
      if (recvfrom (fd, (void *)buf, sizeof (struct udphdr) + 42, 0,
                    (struct sockaddr *)&serv, &addrlen)
          == -1)
        {
          perror ("recv");
          exit (EXIT_FAILURE);
        };
      char *bufp = buf + 20;
      printf ("PACKET!!!\nsrc-port = %d\ndst-port = %d\nlenght = %d\n check = "
              "%d\nmessage:%s\n\n",
              htons (((struct udphdr *)bufp)->source),
              htons (((struct udphdr *)bufp)->dest),
              htons (((struct udphdr *)bufp)->len),
              htons (((struct udphdr *)bufp)->check),
              (bufp + sizeof (struct udphdr)));
    }
  // printf("GOT MESSAGE!  %s\n",hi);}
  printf ("program finished!!!\n");
  getchar ();
  close (fd);
}
