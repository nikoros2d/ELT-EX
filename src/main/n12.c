#include <stdio.h>

int
main ()
{
  FILE *fptr;
  char content[1000];
  gets (content, 1000, stdin);
  fflush (stdin);
  fptr = fopen (content, "r");
  if (fptr != NULL)
    {
      printf ("WE HAVE A WINNER!!!\n");
      fgets (content, 100, fptr);
      printf ("%s", content);
    }
  else
    {
      printf ("ERROR FILE WASNT OPEN!!!%s m\n", content);
    }
}
