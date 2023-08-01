#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#define MAXB 100
#define PATH "/tmp/stream_serv"
#include <sys/socket.h>
#include <sys/types.h>

int
main (int argc, char *argv[])
{
  char *msg = "hello!";
  char hi[MAXB];
  int fd;
  fd = socket (AF_LOCAL, SOCK_STREAM, 0);
  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }
  struct sockaddr_un serv;
  serv.sun_family = AF_LOCAL;
  strncpy (serv.sun_path, PATH, sizeof (serv.sun_path) - 1);
  connect (fd, (struct sockaddr *)&serv, sizeof (serv));
  if (fd == -1)
    {
      perror ("accept");
      exit (EXIT_FAILURE);
    }
  // fgets(msg,MAXB,stdin);
  if (send (fd, msg, sizeof (msg), 0) == -1)
    {
      perror ("send");
      exit (EXIT_FAILURE);
    };
  if (recv (fd, hi, sizeof (hi), 0) == -1)
    {
      perror ("recv");
      exit (EXIT_FAILURE);
    };
  printf ("GOT MESSAGE!  '%s'\n", hi);
  printf ("program finished!!!\n");
  getchar ();
  close (fd);
}
