#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#define MAXB 100 

struct msgbuf{
	long int mtype;
	char msg[MAXB];
	};
	
int main(int argc, char *argv[]) {
  key_t key;
  int msgid;
  long int msgrcv_param = 0;
  struct msgbuf mess;
  char buf1[MAXB];
  key = ftok("n18_1_1",'S');
           if (key == -1) {
               perror("ftok");
               exit(EXIT_FAILURE);
           }
  msgid = msgget(key,0666|IPC_CREAT);  
  //printf("server started!\n");
  fgets(buf1,MAXB,stdin);
  mess.mtype=1;
  if(msgrcv(msgid,(void*)&mess,MAXB,msgrcv_param,0)==-1){
   printf("NOT received ERR!!\n");
  }
  printf("msg received: %s\n",mess.msg);
  strcpy(mess.msg,buf1);
  if(msgsnd(msgid,(void*)&mess,MAXB,0)==-1){
  printf("NOT SEND ERR!!\n");
  }
  printf("program finished!!!\n");
}
