#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 100

typedef struct
{
  char msg[MAXB];
} msgbuf;

int
main (int argc, char *argv[])
{
  struct mq_attr attributes = {
    .mq_flags = 0,
    .mq_maxmsg = 10,
    .mq_msgsize = sizeof (msgbuf),
    .mq_curmsgs = 0,
  };
  mqd_t queue2 = mq_open ("/n18_2_2", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR,
                          &attributes);
  mqd_t queue = mq_open ("/n18_2_1", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR,
                         &attributes);
  msgbuf mess;
  char buf1[MAXB];
  // printf("server started!\n");
  // mq_receive(queue,(char *)&mess, sizeof(mess),NULL);
  // printf("msg received: %s\n",mess.msg);

  fgets (buf1, MAXB, stdin);
  strcpy (mess.msg, buf1);
  mq_send (queue2, (char *)&mess, sizeof (mess), 1);
  mq_close (queue2);
  mq_unlink ("/n18_2_2");
  mq_close (queue);
  mq_unlink ("/n18_2_1");
  printf ("program finished!!!\n");
}
