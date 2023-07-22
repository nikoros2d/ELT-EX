#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>//this whole program does not work whatsoever.
#define maxb 100
int main(){
int i=0,j=0, fd[2];
char k;
char command1[maxb],command2[maxb];
char arg1[maxb][maxb], arg2[maxb][maxb];

        k = getchar();
while(k != ' ' && k != EOF && k != '\n' && k != '|' && i < maxb){
	command1[i]=k;
	i++;
	k = getchar();
    }
    command1[i]='\0';
    i=0;
    if(k == ' '){
    while(k != EOF && k != '\n' && k != '|' && i < maxb){
      k = getchar();
      if(k == ' '){j++;i=0;}
      else if(k == '|'){;}
      else {arg1[i][j]=k;i++;}
     }
    }
    j=0;
    i=0;
    if(k == '|'){    
    
            k = getchar();
            if(k == ' '){k= getchar();}
while(k != ' ' && k != EOF && k != '\n' && k != '|' && i < maxb){
	command2[i]=k;
	i++;
	k = getchar();
    }
    command2[i]='\0';
    i=0;
    if(k == ' '){
    while(k != EOF && k != '\n' && k != '|' && i < maxb){
      k = getchar();
      if(k == ' '){j++;i=0;}
      else {arg2[i][j]=k;i++;}
     }
    }
    
    }
    
    pipe(fd);
    pid_t first = fork();
    if(first){
    dup2(fd[0],0);
     if (execvp(command2, arg2) == -1) {
                        printf("2nd Command not found!\n");
                        exit(EXIT_FAILURE);
                    }    
    }
    else{
    dup2(fd[1],1);
     if (execvp(command1, arg1) == -1) {
                        printf("1st Command not found!\n");
                        exit(EXIT_FAILURE);
                    } 
    
    }
}





























