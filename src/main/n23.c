#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXB 100 
#define PORT 7777
#define PATH "/tmp/stream_serv"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
  char msg[MAXB] = "hi!";
  char hi[MAXB];
  int fd,x=0;
  printf("USE SUDO!!!\n");
  fd = socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
  if(fd == -1){perror("socket");exit(EXIT_FAILURE);}
  struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
  socklen_t addrlen = sizeof(serv);
  while(1){
  if(recvfrom(fd,hi,sizeof(hi),0,(struct sockaddr*)&serv,&addrlen)== -1){perror("recv");exit(EXIT_FAILURE);};
  x++;
  printf("GOT MESSAGE!  %d packets found!\n",x);}
  printf("program finished!!! %d packets found!\n",x);
  getchar();
  close(fd);
}
