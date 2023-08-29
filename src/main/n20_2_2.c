// this is sender
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

void
mysignal (int signal)
{

  printf ("Got the signal\n");
}

int
main (int argc, char **argv)
{
  int fd;
  struct sigaction action;
  char *myfifo = "/tmp/myfifo";
  mkfifo (myfifo, 0666);
  char buf1[MAXB];
  char *buf2;
  printf ("user started!\n");
  fd = open (myfifo, O_RDONLY);
  read (fd, buf1, sizeof (buf1));
  close (fd);
  pid_t *pid;
  pid = buf1;

  action.sa_handler = mysignal;
  sigemptyset (&action.sa_mask);
  action.sa_flags = 0;

  sigaction (SIGUSR1, &action, NULL);

  kill (*pid, SIGUSR1);

  exit (EXIT_SUCCESS);
}
