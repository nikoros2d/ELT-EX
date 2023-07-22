#include <pthread.h>
#include <stdio.h>

int a = 0;

void *
thread_calc (void *argc)
{
  int i;
  int *ptr = (int *)argc;
  for (i = 0; i < 1000000; i++)
    {
      a++;
    }
}

int
main ()
{
  int i, c[1000];
  int *s;
  pthread_t thread[1000];

  for (i = 0; i < 1000; i++)
    {
      c[i] = i;
      pthread_create (&thread[i], NULL, thread_calc, (void *)&c[i]);
    }

  for (i = 0; i < 1000; i++)
    {
      pthread_join (thread[i], (void **)&s);
    }
  printf ("%d\n", a);
} // 58.003.186/1.000.000.000 = 5,8% is registered, other 94,2% is overritten
