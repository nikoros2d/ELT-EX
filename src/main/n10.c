#include "../lib/calcfunc1.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main ()
{
  char *a = (char *)malloc (sizeof (char) * 32);
  ;
  puts ("Enter path to lib:\n");
  fgets (a, 31, stdin);
  a[strcspn (a, "\n")] = '\0';

  puts ("path entered:\n");
  void *libhandle = dlopen (a, RTLD_LAZY);
  if (libhandle == NULL)
    {
      perror ("dlopen");
      return 0;
    }

  int (*func) (int, int);
  char *(*getname) (void);
  getname = dlsym (libhandle, "gname");
  func = dlsym (libhandle, (*getname) ());
  int x;
  puts ("Enter starting number:\n");
  scanf ("%d", &x);
  int y;
  puts ("Enter second number:\n");
  scanf ("%d", &y);
  printf ("%d --> %d\n", x, func (x, y));
  return 0;

  dlclose (libhandle);
}
