#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#define MAXB 100
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
  char hi[MAXB] = "HELP!";
  int fd;
  fd = socket(AF_INET,SOCK_STREAM,0);
  if(fd == -1){perror("socket");exit(EXIT_FAILURE);}
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(11244);
  serv.sin_addr.s_addr = inet_addr("127.0.0.1");
  socklen_t addrlen = sizeof(serv);
  connect(fd,(struct sockaddr *) &serv, addrlen);
  if(fd == -1){perror("accept");exit(EXIT_FAILURE);}
  //fgets(msg,MAXB,stdin);
  if(send(fd,hi,sizeof(hi),0)== -1){perror("send");exit(EXIT_FAILURE);};
  if(recv(fd,hi,sizeof(hi),0)== -1){perror("recv");exit(EXIT_FAILURE);};
  printf("GOT MESSAGE!  '%s'\n",hi);
  printf("program finished!!!\n");
  getchar();
  close(fd);
}
