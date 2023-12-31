#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h> //this is user
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

char name[MAXB];

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
  msgbuf mess;
  mqd_t queue = mq_open ("/n18_3_1", O_RDONLY | O_CREAT, 0666, &attributes);
  while (1)
    {
      mq_receive (queue, (char *)&mess, sizeof (mess), NULL);
      printf ("msg received:   %s\n", mess.msg);
    }
  mq_close (queue);
  mq_unlink ("/n18_3_1");
}

void *
thread_snd (void *argv)
{
  char buf1[MAXB];
  msgbuf mess;
  mqd_t queue = mq_open ("/n18_3_2", O_WRONLY | O_CREAT, 0666, &attributes);
  while (1)
    {
      strcpy (mess.msg, name);
      strcat (mess.msg, ":");
      fgets (buf1, MAXB, stdin);
      strcat (mess.msg, buf1);
      mq_send (queue, (char *)&mess, sizeof (mess), 1);
    }
  mq_close (queue);
  mq_unlink ("/n18_3_2");
}

int
main (int argc, char *argv[])
{
  char buf1[MAXB];
  int *c[2];
  printf ("user started!\n");
  msgbuf mess;
  mqd_t queue = mq_open ("/n18_3_3", O_WRONLY | O_CREAT, 0666, &attributes);
  printf ("ENTER YOUR NICKNAME:\n");
  fgets (buf1, MAXB, stdin);
  strncpy (name, buf1, (strlen (buf1) - 1));
  strcpy (mess.msg, name);
  mq_send (queue, (char *)&mess, sizeof (mess), 1);
  pthread_t thread[2];
  pthread_create (&thread[0], NULL, thread_rcv, (void *)&c[0]);
  pthread_create (&thread[1], NULL, thread_snd, (void *)&c[1]);
  pthread_join (thread[1], (void **)&c);
  pthread_join (thread[0], (void **)&c);
  mq_close (queue);
  mq_unlink ("/n18_3_3");
  printf ("program finished!!!\n");
}
