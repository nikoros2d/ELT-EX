#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //broadcast receiver
#include <sys/types.h>

#define SPORT 7777
#define PORT 8989

int
main (int argc, char **argv)
{
  int size = 1;

  socklen_t addr_size;

  struct sockaddr_in client;

  int fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  memset (&client, 0, sizeof (struct sockaddr_in));
  client.sin_family = AF_INET;
  client.sin_port = htons (PORT);
  client.sin_addr.s_addr = INADDR_ANY;
  int ok = bind (fd, (struct sockaddr *)&client, sizeof (struct sockaddr_in));
  if (ok < 0)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }

  char buffer[128];
  addr_size = sizeof (struct sockaddr_in);
  if (recvfrom (fd, buffer, 64, 0, NULL, NULL) < 0)
    {
      perror ("recvfrom");
      exit (EXIT_FAILURE);
    };
  printf ("GOT MESSAGE:%s\n", buffer);

  close (fd);

  exit (EXIT_SUCCESS);
}
