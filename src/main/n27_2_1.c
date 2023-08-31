#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //multicast receiver
#include <sys/types.h>

#define IP "224.2.2.4"
#define SPORT 7777
#define PORT 8888

int
main (int argc, char **argv)
{

  char *buffer = malloc (64);
  socklen_t addr_size;

  struct sockaddr_in client, receiver;

  int fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (-1 == fd)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  memset (&client, 0, sizeof (struct sockaddr_in));
  client.sin_family = AF_INET;
  client.sin_port = htons (PORT);
  client.sin_addr.s_addr = INADDR_ANY;

  struct in_addr imr_multiaddr;
  struct ip_mreqn op;
  op.imr_address.s_addr = INADDR_ANY;
  op.imr_multiaddr.s_addr = inet_addr (IP);
  op.imr_ifindex = 2; // if_nametoindex("");//iface name here

  // struct ip_mreqn { struct in_addr imr_multiaddr;
  // struct inaddr imr_address;
  // int imr_ifindex;};

  if (setsockopt (fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &op, sizeof (op)) < 0)
    {
      perror ("setsockopt");
      exit (EXIT_FAILURE);
    }

  if (-1 == bind (fd, (struct sockaddr *)&client, sizeof (struct sockaddr_in)))
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }

  bzero (buffer, 64);
  addr_size = sizeof (struct sockaddr_in);
  recvfrom (fd, buffer, 64, 0, NULL, NULL);
  printf ("GOT MESSAGE:%s\n", buffer);

  close (fd);

  exit (EXIT_SUCCESS);
}
