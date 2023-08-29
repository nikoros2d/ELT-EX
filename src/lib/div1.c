#include "calcfunc1.h"
#include "stdio.h"

char *
gname ()
{
  return "div1";
}

int
div1 (int x, int y)
{
  if (y == 0)
    return -1;
  return x / y;
}
