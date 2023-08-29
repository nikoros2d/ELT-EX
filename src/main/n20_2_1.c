#include <fcntl.h>
#include <signal.h> //this is receiver
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

int
main ()
{
  sigset_t *newset;
  sigset_t *oldset;
  int *signumber;
  int fd;
  char *myfifo = "/tmp/myfifo";
  mkfifo (myfifo, 0666);
  char buf1[MAXB];
  char *buf2;
  printf ("user started!\n");

  pid_t pid;
  char *msg;
  pid = getpid ();
  buf2 = &pid;
  fd = open (myfifo, O_WRONLY);
  write (fd, buf2, strlen (buf2) + 1);
  printf ("PID SENT!");
  close (fd);
  sigemptyset (newset);
  sigaddset (newset, 10);
  sigprocmask (SIG_BLOCK, newset, oldset);
  printf ("Process is running!\n");
  while (1)
    {
      sigwait (newset, signumber);
      if (signumber != NULL)
        {
          break;
        }
    }

  printf ("Signal received %d!\n", *signumber);

  exit (EXIT_SUCCESS);
}
