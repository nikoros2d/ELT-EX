#include <stdio.h>
#include "../lib/calcfunc.h"

int main(){
int res,x;
 printf("enter starting number >");
 scanf("%d",&res);
 fflush(stdin);
while(1){
 printf("\n1 - ADD\n2 - SUB\n3 - MUL\n4 - DIV\nELSE = EXIT\n\nENTER OPTION >");
 scanf("%d",&x);
 fflush(stdin);
 printf("\n");
 switch(x){
  case 1:{res = add(res);
          break;
}
  case 2:{res = sub(res);
          break;
}
  case 3:{res = mul(res);
          break;
}
  case 4:{res = div(res);
          break;
}
  default:{printf("resoult - %d",res);return 0;}
}
}
}
