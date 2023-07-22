#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100
int
main (void)
{
  int fd;
  char *myfifo = "/tmp/myfifo";
  mkfifo (myfifo, 0666);
  char buf1[MAXB];
  char *buf2;
  printf ("user started!\n");
  fd = open (myfifo, O_RDONLY);
  read (fd, buf1, sizeof (buf1));
  printf ("SERVER: %s\n", buf1);
  close (fd);
  fd = open (myfifo, O_WRONLY);
  buf2 = "USER SENT MSG!";
  write (fd, buf2, strlen (buf2) + 1);
  close (fd);
}
