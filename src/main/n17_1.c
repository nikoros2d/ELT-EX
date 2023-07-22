#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void) {
  int fd[2];  //c->p
  int fd1[2]; //p->c
  if(pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  if(pipe(fd1) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
 printf("pipe created!!\n");
 int pid = fork();
 if(pid == 0){
 int x=0;
 close(fd1[0]);
 close(fd[1]);
 read(fd[0],&x,sizeof(x));
 printf("got x=%d\n",x); 
 x=x*x;
 write(fd1[1],&x,sizeof(x));
 }
 else{
 int x=5;
 close(fd1[1]);
 close(fd[0]);
 write(fd[1],&x,sizeof(x));
 printf("sent x=%d\n",x); 
 read(fd1[0],&x,sizeof(x));
 printf("got resoult x=%d\n",x);
 } 
  return EXIT_SUCCESS;
}
