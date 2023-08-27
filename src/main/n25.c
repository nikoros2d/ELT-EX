#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXB 100 
#define PORT 7777
#define SPORT 8888 
#define PATH "/tmp/stream_serv"
#define SADDR "127.0.0.1"
#define DADDR "127.0.0.2"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <unistd.h>
#include <linux/ip.h>
#include <sys/types.h>
//#define _GNU_SOURCE


int main(int argc, char *argv[]) {
    char hi[MAXB]="HELLO 4567!";
    char* msg = (char*)malloc(sizeof(struct udphdr));
    char* ip = (char*)malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(hi));

    ((struct iphdr*)ip)->version = 4;
    ((struct iphdr*)ip)->ihl = 5;
    
    ((struct iphdr*)ip)->tot_len = 0;//sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof("help")+64000;
    ((struct iphdr*)ip)->id = htons(1);
    ((struct iphdr*)ip)->frag_off = htons(0);
    ((struct iphdr*)ip)->ttl = 4;
    ((struct iphdr*)ip)->protocol = IPPROTO_UDP;
    ((struct iphdr*)ip)->check = 0;
    ((struct iphdr*)ip)->saddr = inet_addr(SADDR);
    ((struct iphdr*)ip)->daddr = inet_addr(DADDR);
    ((struct iphdr*)ip)->tos = 0;
    
    
    ((struct udphdr*)msg)->source = htons(PORT);
    ((struct udphdr*)msg)->dest = htons(SPORT);
    ((struct udphdr*)msg)->check = htons(0);
    ((struct udphdr*)msg)->len = htons(sizeof(struct udphdr)+sizeof(hi));// + sizeof(hi)+20);
    
    strncpy(ip + sizeof(struct iphdr), msg,sizeof(struct udphdr));
    strcpy(ip + sizeof(struct iphdr) + sizeof(struct udphdr), hi);

    if(!strcmp(ip + sizeof(struct iphdr) + sizeof(struct udphdr),hi))printf("BUFFER IS FULL!\n");
    printf("\n%d\n",sizeof(hi));
    for(int jj=1;jj<(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(hi));jj++){printf("%d",ip[jj]);}
    
  int fd,sso,gso;
  int enabled=1;
   int enabled1=3;
  printf("USE SUDO!!!\n");
  fd = socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
  if(fd == -1){perror("socket");exit(EXIT_FAILURE);}
 // sso = setsockopt(fd, IPPROTO_IP, IP_OPTIONS,  &enabled, sizeof(enabled)); //this is for specific changes
 sso = setsockopt(fd, IPPROTO_IP, IP_HDRINCL,  &enabled, sizeof(enabled));       //and this wrecks package beyond repair 
   if(sso<0)                                                                        //so beyond, in fact, that it doesnt even let me edit the header its just set to 0001
      printf("errore setsockoptions\n");
      
  /*gso = getsockopt(fd, IPPROTO_IP, IP_HDRINCL,  enabled1, (void*)sizeof(enabled1)); //this just does not work
   if(gso<0)
      printf("errore GGGGetsockoptions\n");
      printf("SSO=%d\nGSO=%d\nOPT=%d\n",sso,gso,enabled1);
 //*/     
      
      
  struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  socklen_t addrlen = sizeof(serv);
  
  
  if(sendto(fd,(void*)ip,sizeof(struct udphdr)+sizeof(struct iphdr)+sizeof("help"),0,(struct sockaddr*)&serv,addrlen)== -1){perror("send");exit(EXIT_FAILURE);}
  
  close(fd);
  free(ip);
  free(msg);
}
