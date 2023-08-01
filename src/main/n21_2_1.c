#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#define MAXB 100 
#define PATH "/tmp/stream_serv"
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
  char msg[MAXB];
  char hi[MAXB] = "Hi from serv!";
  int Fd;
  Fd = socket(AF_LOCAL,SOCK_DGRAM,0);
  if(Fd == -1){perror("socket");exit(EXIT_FAILURE);;}
  struct sockaddr_un serv;
  serv.sun_family = AF_LOCAL;
  strcpy(serv.sun_path,PATH);
  struct sockaddr_un client;
  if(bind(Fd,(struct sockaddr *) &serv,sizeof(serv))== -1){perror("bind");exit(EXIT_FAILURE);};
  socklen_t addrlen = sizeof(serv);
  //client.sun_family = AF_LOCAL;
  //strncpy(client.sun_path,PATH,sizeof(client.sun_path)-1);
  
  //listen(Fd,5);
  if(recvfrom(Fd,msg,sizeof(msg),0,(struct sockaddr*)&serv,&addrlen)== -1){perror("recvfrom");exit(EXIT_FAILURE);};
  printf("GOT MESSAGE!  '%s'\n",msg);
  if(sendto(Fd,hi,sizeof(hi)*10,0,(struct sockaddr*)&serv,addrlen)== -1){perror("sendto");exit(EXIT_FAILURE);};
  printf("program finished!!!\n");
  getchar();
  //close(Fd);
  //unlink("/tmp/stream_serv");
}
