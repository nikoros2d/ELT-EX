#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <mqueue.h>
#include <pthread.h> //this is server
#define MAXB 100 

typedef struct {
	char msg[MAXB];
	} msgbuf;
	
struct mq_attr attributes = {
  .mq_flags = 0,
  .mq_maxmsg = 10,
  .mq_msgsize = sizeof(msgbuf),
  .mq_curmsgs = 0,
  };

void *thread_rcv(void *argv){
  msgbuf mess;
  mqd_t queue = mq_open("/n18_2_2", O_RDONLY | O_CREAT,S_IRUSR | S_IWUSR ,&attributes);
  while(1){
  mq_receive(queue,(char *)&mess, sizeof(mess),NULL);
  printf("msg received: %s\n",mess.msg);
  }
  mq_close(queue);
  mq_unlink("/n18_2_2");
}

void *thread_snd(void *argv){
  char buf1[MAXB];
  msgbuf mess;
  mqd_t queue = mq_open("/n18_2_1", O_WRONLY | O_CREAT,S_IRUSR | S_IWUSR ,&attributes);
  while(1){
  fgets(buf1,MAXB,stdin);
  strcpy(mess.msg,buf1);
  mq_send(queue,(char *)&mess,sizeof(mess),1);
  }
  mq_close(queue);
  mq_unlink("/n18_2_1");
}

int main(int argc, char *argv[]) {  
  int *c[2];
  printf("server started!\n");
  pthread_t thread[2];
  pthread_create(&thread[0],NULL, thread_rcv, (void *) &c[0]);
  pthread_create(&thread[1],NULL, thread_snd, (void *) &c[1]);
  pthread_join(thread[1], (void **) &c);
  pthread_join(thread[0], (void **) &c);
  
  printf("program finished!!!\n");
}

