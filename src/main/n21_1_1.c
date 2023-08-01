#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#define MAXB 100
#define PATH "/tmp/stream_serv"
#include <sys/socket.h>
#include <sys/types.h>

int
main (int argc, char *argv[])
{
  char msg[MAXB];
  char *hi = "Hi from serv!";
  int Fd, nfd, valread;
  Fd = socket (AF_LOCAL, SOCK_STREAM, 0);
  if (Fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
      ;
    }
  struct sockaddr_un serv;
  socklen_t addrlen = sizeof (struct sockaddr_un);
  serv.sun_family = AF_LOCAL;
  strncpy (serv.sun_path, PATH, sizeof (serv.sun_path) - 1);
  struct sockaddr_un client;
  memset (&client, 0, sizeof (struct sockaddr_un));
  serv.sun_family = AF_LOCAL;
  strncpy (serv.sun_path, PATH, sizeof (client.sun_path) - 1);
  if (bind (Fd, (struct sockaddr *)&serv, sizeof (serv)) == -1)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    };
  listen (Fd, 5);
  nfd = accept (Fd, (struct sockaddr *)&client, &addrlen);
  if (nfd == -1)
    {
      perror ("accept");
      exit (EXIT_FAILURE);
    }
  else
    printf ("accept granted? \n");
  if (recv (nfd, msg, sizeof (msg), 0) == -1)
    {
      perror ("recv");
      exit (EXIT_FAILURE);
    };
  printf ("GOT MESSAGE!  '%s'\n", msg);
  if (send (nfd, hi, sizeof (hi) * 10, 0) == -1)
    {
      perror ("send");
      exit (EXIT_FAILURE);
    };
  printf ("program finished!!!\n");
  getchar ();
  close (nfd);
  close (Fd);
}
