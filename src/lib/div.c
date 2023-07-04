#include "calcfunc.h"
#include "stdio.h"
int
div (int res)
{
  int x;
  while (1)
    {
      printf ("%d / ", res);
      scanf ("%d", &x);
      fflush (stdin);
      if (x == 0)
        printf ("\ncannot divide by 0\n");
      else
        break;
    }
  printf ("%d = %d\n", x, res / x);
  return res / x;
}
