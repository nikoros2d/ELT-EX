#include "calcfunc.h"
#include "stdio.h"
int
sub (int res)
{
  int x;
  printf ("%d - ", res);
  scanf ("%d", &x);
  fflush (stdin);
  printf ("%d = %d\n", x, res - x);
  return res - x;
}
