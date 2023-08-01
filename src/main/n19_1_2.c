#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define MAXB 100 
#define err -1
#define pathmsg "n19_1_1"
#define permissions 0666
	
int main(int argc, char *argv[]) {
   printf("HELLO?!\n");
  //key_t key;
 // key = ftok(pathmsg,0);
  //if(key == err){printf("key err\n");return err;};
  int msg_shm = shmget(1234,MAXB, permissions | IPC_CREAT);
  char* resoult;
  resoult = shmat(msg_shm,NULL,0); 
  char msg[MAXB];

  fgets(msg,MAXB,stdin);
  strcpy(resoult,msg);
  shmdt(resoult); //detach
  //shmctl(msg_shm,IPC_RMID,NULL); //destroy
} 
