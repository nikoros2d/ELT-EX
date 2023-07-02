#include <stdio.h>

void first(){
 int n = 3;
 int mas[n][n];
 printf("first\n");
 for (int i=0;i<n;i++){
  for (int j=0;j<n;j++){
   mas[i][j]=i*n+j+1;
   printf("%2d ",mas[i][j]);
  }
  printf("\n");
 }
}

void second(){
 int n = 5;
 int mas[n];
 printf("second\n");
 for (int i=0;i<n;i++){
  mas[i] = i+1;
  printf("%2d ",mas[i]);}
 printf("\n");
 for (int i=n-1;i>-1;i--)
  printf("%2d ",mas[i]);
 printf("\n");
}

void third(){
 int n = 3;
 int mas[n][n];
 printf("third\n");
 for(int i=0;i<n;i++){
  for(int j=0;j<n;j++){
   if((i+j+1)<n)mas[i][j]=0;
   else mas[i][j]=1;
   printf("%2d ",mas[i][j]);
  }
  printf("\n");
 }
}

void fourth(){
	int n=9,i,mas[n][n],c=n,x=1,k=1,move[]={0,0,0,0};
 printf("fourth\n");
	while(c>0){
			switch(x){
				case 1:{
					for(i=0;i<c;i++){
					mas[move[0]][i+move[3]]=k;
					k++;	
					}
					c--;x++;move[0]++;
					break;
				}
				case 2:{
					for(i=0;i<c;i++){
					mas[i+move[0]][n-1-move[1]]=k;
					k++;	
					}
					x++;move[1]++;
					break;
				}
				case 3:{
					for(i=0;i<c;i++){
					mas[n-1-move[2]][(n-1-move[1])-i]=k;
					k++;	
					}
					c--;x++;move[2]++;
					break;
				}
				case 4:{
					for(i=0;i<c;i++){
					mas[n-1-move[2]-i][move[3]]=k;
					k++;	
					}
					x=1;move[3]++;
					break;
				}
			}
		}
	for(i=0;i<n;i++){
		for(k=0;k<n;k++){
			printf("%2d ",mas[i][k]);
		}
		printf("\n");
	}
}

void main(){
 first();
 second();
 third();
 fourth();
}
