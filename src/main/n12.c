#include <stdio.h>

int
main ()
{
  FILE *fptr;
  fptr = fopen ("test.txt", "r");
  char content[1000];
  if (fptr != NULL)
    {
      printf ("WE HAVE A WINNER!!!\n");
      fgets (content, 100, fptr);
      printf ("%s", content);
    }
  else
    {
      printf ("FUCK YOU LOSER!!!\n");
    }
}
