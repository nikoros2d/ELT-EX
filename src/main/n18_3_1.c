#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h> //this is server
#include <stdio.h>   //this works, but havent figured out how to attach nicknames
#include <stdlib.h>  //cool thing actually
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

int n;
 
typedef struct
{
  char msg[MAXB];
} msgbuf;

struct mq_attr attributes = {
  .mq_flags = 0,
  .mq_maxmsg = 10,
  .mq_msgsize = sizeof (msgbuf),
  .mq_curmsgs = 0,
};

void *
thread_rcv (void *argv)
{ 
  int j;
  mqd_t queue2 = mq_open ("/n18_3_1", O_WRONLY | O_CREAT, 0666,
                         &attributes);
  msgbuf mess;
  mqd_t queue = mq_open ("/n18_3_2", O_RDONLY | O_CREAT, 0666,
                         &attributes);
  while (1)
    {
      mq_receive (queue, (char *)&mess, sizeof (mess), NULL);
      printf ("n=%d   msg received: %s\n",n, mess.msg);
      for(j=0;j<n+1;j++){
       mq_send (queue2, (char *)&mess, sizeof (mess), 1);
      }
    }
  mq_close (queue);
  mq_unlink ("/n18_3_2");
  mq_close (queue);
  mq_unlink ("/n18_3_1");
}

void *
thread_init (void *argv)
{ 
  int newusr=1,j;
  n=0;
  char *users[MAXB];
  msgbuf mess;
  mqd_t queue = mq_open ("/n18_3_3", O_RDONLY | O_CREAT, 0666,
                         &attributes);
  while (1)
    { 
      mq_receive (queue, (char *)&mess, sizeof (mess), NULL);
      printf ("user %s logged in\n", mess.msg);
      for(j=0;j<n;j++){
       if(strcmp(mess.msg,users[j])==0)newusr=0;
      }
      if(newusr){users[n]=mess.msg;n++;}
      newusr=1;
    }
  mq_close (queue);
  mq_unlink ("/n18_3_3");
}

int
main (int argc, char *argv[])
{
  int *c[2];
  printf ("server started!\n");
  pthread_t thread[2];
  pthread_create (&thread[0], NULL, thread_rcv, (void *)&c[0]);
  pthread_create (&thread[1], NULL, thread_init, (void *)&c[1]);
  pthread_join (thread[1], (void **)&c);
  pthread_join (thread[0], (void **)&c);

  printf ("program finished!!!\n");
}
