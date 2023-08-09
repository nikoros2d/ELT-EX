#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXB 100 
#define PORT 7777
#define SPORT 8888 
#define PATH "/tmp/stream_serv"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/udp.h>
#include <unistd.h>
#include <linux/ip.h>
//#define _GNU_SOURCE


int main(int argc, char *argv[]) {
    char hi[MAXB]="HELLO 456!";
    char* packed = (char*)malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(hi));
    char* callback_buff = (char*)malloc(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(hi));
    ((struct iphdr*)packed)->version = htons(0b0100);//0b01000101;//putting 4 in ipv4 and 5 in IHL
    ((struct iphdr*)packed)->ihl = htons(5);
    //((struct iphdr*)packed)->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(hi));
    ((struct iphdr*)packed)->id = 0;
    ((struct iphdr*)packed)->frag_off = htons(0x40);
    ((struct iphdr*)packed)->ttl = 68;//time to live
    ((struct iphdr*)packed)->protocol = htons(0x17);
    ((struct iphdr*)packed)->check = htons(0);
    ((struct iphdr*)packed)->saddr = htonl(INADDR_LOOPBACK);
    ((struct iphdr*)packed)->daddr = htonl(INADDR_LOOPBACK);
    ((struct iphdr*)packed)->tos = htons(0);
    
    packed += sizeof(struct iphdr);

    ((struct udphdr*)packed)->source = htons(PORT);
    ((struct udphdr*)packed)->dest = htons(SPORT);
    ((struct udphdr*)packed)->len = htons(sizeof(struct udphdr) + sizeof(hi));
    ((struct udphdr*)packed)->check = htons(0);
    
    if (!strncpy(packed + sizeof(struct udphdr), hi, MAXB)) {
        printf("buffer full error\n");
    }
    
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
      
  gso = getsockopt(fd, IPPROTO_IP, IP_HDRINCL,  enabled1, (void*)sizeof(enabled1)); //this just does not work
   if(gso<0)
      printf("errore GGGGetsockoptions\n");
      printf("SSO=%d\nGSO=%d\nOPT=%d\n",sso,gso,enabled1);
 //*/     
      
      
  struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  socklen_t addrlen = sizeof(serv);
  
  
  if(sendto(fd,(void*)packed,sizeof(struct udphdr)+sizeof(struct iphdr)+sizeof(hi),0,(struct sockaddr*)&serv,addrlen)== -1){perror("send");exit(EXIT_FAILURE);}
  while(1){
  if(recvfrom(fd,(void*)callback_buff,sizeof(struct udphdr)+sizeof(struct iphdr)+sizeof(hi),0,(struct sockaddr*)&serv,&addrlen)== -1){perror("recv");exit(EXIT_FAILURE);}
  printf("PACKET!!!\nMSG:%s\n",callback_buff+sizeof(struct udphdr)+sizeof(struct iphdr));
    printf("VERSION :%d\n",((struct iphdr*)callback_buff)->version);
    printf("TOTALLEN:%d\n",htons(((struct iphdr*)callback_buff)->tot_len));
    printf("ID      :%d\n",htons(((struct iphdr*)callback_buff)->id));
    printf("FLAG    :%d\n",((struct iphdr*)callback_buff)->frag_off);
    printf("TTL     :%d\n",((struct iphdr*)callback_buff)->ttl);//time to live
    printf("PROTOCOL:%d\n",((struct iphdr*)callback_buff)->protocol);
    printf("CHECKSUM:%d\n",htons(((struct iphdr*)callback_buff)->check));
    printf("SENDADDR:%d\n",((struct iphdr*)callback_buff)->saddr);
    printf("DESTADDR:%d\n",htons(((struct iphdr*)callback_buff)->daddr));
    printf("TOS     :%d\n",htons(((struct iphdr*)callback_buff)->tos));
    
    callback_buff += sizeof(struct iphdr);

    printf("SOURPORT:%d\n",htons(((struct udphdr*)callback_buff)->source));
    printf("DESTPORT:%d\n",htons(((struct udphdr*)callback_buff)->dest));
    printf("LENGHT  :%d\n",htons(((struct udphdr*)callback_buff)->len));
    printf("CHECK  2:%d\n",htons(((struct udphdr*)callback_buff)->check));
  }
  printf("program finished!!!\n");
  getchar();
  free(packed);
    free(callback_buff);
  close(fd);
}
