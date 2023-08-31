#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/udp.h> //broadcast sender
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define IP "192.168.0.255"
#define SPORT 7777
#define PORT 8989

int
main (int argc, char *argv[])
{

  char *msg = "HI 1245251!";
  printf ("%s\n", msg);

  int fd = socket (AF_INET, SOCK_DGRAM, 0);

  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  struct sockaddr_in serv;
  memset (&serv, 0, sizeof (struct sockaddr_in));
  serv.sin_family = AF_INET;
  serv.sin_port = htons (PORT);
  serv.sin_addr.s_addr = inet_addr (IP);
  socklen_t addrlen = sizeof (serv);

  int enabled = 1;
  if (setsockopt (fd, SOL_SOCKET, SO_BROADCAST, &enabled, sizeof (enabled))
      < 0)
    {
      perror ("setsockopt");
      exit (EXIT_FAILURE);
    }

  if (sendto (fd, msg, strlen (msg), 0, (struct sockaddr *)&serv, addrlen) < 0)
    {
      perror ("sendto");
      exit (EXIT_FAILURE);
    }

  close (fd);

  exit (EXIT_SUCCESS);
}
