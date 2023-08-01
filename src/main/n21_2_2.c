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
  char msg[MAXB] = "hi!";
  char hi[MAXB];
  int fd;
  fd = socket (AF_LOCAL, SOCK_DGRAM, 0);
  if (fd == -1)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }
  struct sockaddr_un serv;
  serv.sun_family = AF_LOCAL;
  strcpy (serv.sun_path, PATH);
  if (connect (fd, (struct sockaddr *)&serv, sizeof (serv)) == -1)
    {
      perror ("accept");
      exit (EXIT_FAILURE);
    }
  socklen_t addrlen = sizeof (serv);
  // fgets(msg,MAXB,stdin);
  if (sendto (fd, msg, sizeof (msg), 0, (struct sockaddr *)&serv, addrlen)
      == -1)
    {
      perror ("send");
      exit (EXIT_FAILURE);
    };
  if (recvfrom (fd, hi, sizeof (hi), 0, (struct sockaddr *)&serv, &addrlen)
      == -1)
    {
      perror ("recv");
      exit (EXIT_FAILURE);
    };
  printf ("GOT MESSAGE!  '%s'\n", hi);
  printf ("program finished!!!\n");
  getchar ();
  // close(fd);
}
