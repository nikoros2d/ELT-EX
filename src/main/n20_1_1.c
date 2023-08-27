#include <signal.h>//this is receiver
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

int main() {

	int fd,i=0;
  char *myfifo = "/tmp/myfifo";
  mkfifo (myfifo, 0666);
  char buf1[MAXB];
  char *buf2;
  printf ("user started!\n");
  
	pid_t pid;
	char* msg;
	pid = getpid();
	buf2 = &pid;
	fd = open (myfifo, O_WRONLY);
  write (fd, buf2, strlen (buf2) + 1);
  printf("PID SENT!");
  close (fd);
	while (1) {
	
		printf("%3d Process is still running!\n",i);
		sleep(2);
		i++;
	}

	exit(EXIT_SUCCESS);
	
}
