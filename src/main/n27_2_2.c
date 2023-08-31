#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/udp.h> //multicast sender
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IP "224.2.2.4"
#define SPORT 7777
#define DPORT 8888

int
main (int argc, char *argv[])
{

  char *msg = "HI 1245251!";
  // printf("%s\n", msg);

  int fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  struct sockaddr_in serv;
  memset (&serv, 0, sizeof (struct sockaddr_in));
  serv.sin_family = AF_INET;
  serv.sin_port = htons (DPORT);
  serv.sin_addr.s_addr = inet_addr (IP);
  socklen_t addrlen = sizeof (serv);
  int enabled = 1;
  struct in_addr imr_multiaddr;
  imr_multiaddr.s_addr = inet_addr (IP);
  if (setsockopt (fd, IPPROTO_IP, IP_MULTICAST_TTL, &enabled,
                  sizeof (enabled)))
    { // &imr_multiaddr, sizeof(imr_multiaddr)) < 0){
      perror ("setsockopt");
      exit (EXIT_FAILURE);
    }
  if (-1
      == sendto (fd, msg, strlen (msg), 0, (struct sockaddr *)&serv, addrlen))
    {
      perror ("sendto");
      exit (EXIT_FAILURE);
    }
  close (fd);

  exit (EXIT_SUCCESS);
}
