#include "../lib/calcfunc.h"
#include <stdio.h>

int
main ()
{
  int res, x;
  printf ("enter starting number >");
  scanf ("%d", &res);
  fflush (stdin);
  while (1)
    {
      printf ("\n1 - ADD\n2 - SUB\n3 - MUL\n4 - DIV\nELSE = EXIT\n\nENTER "
              "OPTION >");
      scanf ("%d", &x);
      fflush (stdin);
      printf ("\n");
      if(x==1){res = add (res);}
      else if(x==2){res = sub (res);}
      else if(x==3){res = mul (res);}
      else if(x==4){res = div (res);}
      else {printf ("resoult - %d", res);
            return 0;}
    }
}
