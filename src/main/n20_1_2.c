//this is sender
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

int main(int argc, char** argv) {
	int fd;
  char *myfifo = "/tmp/myfifo";
  mkfifo (myfifo, 0666);
  char buf1[MAXB];
  char *buf2;
  printf ("user started!\n");
  fd = open (myfifo, O_RDONLY);
  read (fd, buf1, sizeof (buf1));
  close (fd);
  pid_t* pid;
	pid = buf1;

	kill(*pid, 9);

	exit(EXIT_SUCCESS);
}
