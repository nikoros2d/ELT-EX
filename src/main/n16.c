#include <pthread.h>
#include <stdio.h>
int sleep_customer = 0;
int sleep_calc = 0;

pthread_mutex_t m[5] = PTHREAD_MUTEX_INITIALIZER;

struct customer
{
  int num;
  int demand;
};

int a[5] = { 1000, 1000, 1000, 1000, 1000 };

void *
thread_calc (void *argc)
{
  int i;
  while (1)
    {
      for (i = 0; i < 5; i++)
        {
          pthread_mutex_lock (&m[i]);
          a[i] = a[i] + 500;
          sleep (2);
          sleep_calc++;
          pthread_mutex_unlock (&m[i]);
        }
    }
}

void *
thread_customer (void *argc)
{
  int *ptr = (int *)argc;
  while (1)
    {
      pthread_mutex_lock (&m[ptr[0]]);
      ptr[1] = ptr[1] - a[ptr[0]];
      a[ptr[0]] = 0;
      if (ptr[1] == 0)
        {
          printf ("FINISHED THREAD NUM %d, DEMAND = %d\n", ptr[0], ptr[1]);
          break;
        }
      sleep (1);
      sleep_customer++;
      pthread_mutex_unlock (&m[ptr[0]]);
      printf ("THREAD NUM %d, DEMAND = %d\n", ptr[0], ptr[1]);
    }
}

int
main ()
{
  int i;
  int *s;
  struct customer custom[3];
  pthread_t thread[4];
  pthread_create (&thread[0], NULL, thread_calc, (void *)&custom[i]);
  for (i = 1; i < 4; i++)
    {
      custom[i - 1].num = i - 1;
      custom[i - 1].demand = 3000;
      pthread_create (&thread[i], NULL, thread_customer,
                      (void *)&custom[i - 1]);
    }

  for (i = 1; i < 4; i++)
    {
      pthread_join (thread[i], (void **)&s);
    }
  pthread_cancel (thread[0]);
  for (i = 0; i < 5; i++)
    {
      printf ("%d   ", a[i]);
    }
  printf ("\n");
  printf ("sleep calc = %d, sleep customer = %d\n", sleep_calc,
          sleep_customer);
}
