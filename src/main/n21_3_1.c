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
  char msg[MAXB];
  int Fd,nfd;
  Fd = socket(AF_INET,SOCK_STREAM,0);
  if(Fd == -1){perror("socket");exit(EXIT_FAILURE);;}
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(11244);
  serv.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
  struct sockaddr_in client;
  socklen_t addrlen = sizeof(client);
  //client.sin_family = AF_INET;
  //client.sin_port = htons(12345);
  //client.sin_addr.s_addr = inet_addr("127.0.0.1");
  if(bind(Fd,(struct sockaddr *) &serv,sizeof(serv))== -1){perror("bind");exit(EXIT_FAILURE);};
  listen(Fd,1);
  if((nfd=accept(Fd,(struct sockaddr *)&client, &addrlen)) == -1){perror("accept");exit(EXIT_FAILURE);}
  else printf("accept granted!\n");
  if(recv(nfd,msg,sizeof(msg),0)== -1){}//perror("recv");exit(EXIT_FAILURE);};
  printf("GOT MESSAGE!  '%s'\n",msg);
  msg[2]='D';
  msg[3]='E';
  msg[4]='E';
  if(send(nfd,msg,sizeof(msg),0)== -1){perror("send");exit(EXIT_FAILURE);};
  printf("program finished!!!\n");
  getchar();
  close(nfd);
  close(Fd);
}
