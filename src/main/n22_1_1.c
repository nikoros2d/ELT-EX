#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> //client
#include <sys/time.h>
#include <sys/types.h>

#define addr "127.0.0.1"
#define port "8888"

int
main (int args, char **argv)
{

  int request_fd;

  char *received_msg = (char *)malloc (256);
  char *sended_msg = "Hello 12346";

  short *addrport;

  struct sockaddr_in server, subserver;

  socklen_t length;

  request_fd = socket (AF_INET, SOCK_DGRAM, 0);
  if (request_fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr (addr);
  server.sin_port = htons (atoi (port));

  sendto (request_fd, sended_msg, strlen (sended_msg), 0,
          (struct sockaddr *)&server, sizeof (struct sockaddr_in));

  printf ("Waiting for message...\n");
  memset (&subserver, '\0', sizeof (subserver));
  recvfrom (request_fd, received_msg, sizeof (received_msg), 0,
            (struct sockaddr *)&server, sizeof (struct sockaddr_in));

  addrport = received_msg;

  printf ("msg received: %d\n", *addrport);

  server.sin_port = htons (*addrport);

  sendto (request_fd, sended_msg, strlen (sended_msg), 0,
          (struct sockaddr *)&server, sizeof (struct sockaddr_in));

  recvfrom (request_fd, received_msg, 256, 0, (struct sockaddr *)&server,
            sizeof (struct sockaddr_in));

  printf ("Time: %s\n", received_msg);

  exit (EXIT_SUCCESS);
}
