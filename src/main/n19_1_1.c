#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define MAXB 100
#define err -1
#define pathmsg "/n19_1_1"
#define permissions 0666

int
main (int argc, char *argv[])
{
  // key_t key;
  // key = ftok(pathmsg,0);
  // if(key == err)return err;
  int msg_shm = shmget (1234, MAXB, permissions | IPC_CREAT);
  char *resoult;
  resoult = shmat (msg_shm, NULL, 0);

  printf ("%s\n", resoult);
  shmdt (resoult);                  // detach
  shmctl (msg_shm, IPC_RMID, NULL); // destroy
}
