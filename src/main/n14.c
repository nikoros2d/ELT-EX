#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *
sgets (char *buff, unsigned int size)
{

  int i, k = getchar ();

  if (k == EOF)
    {
      return NULL;
    }

  for (i = 0; k != EOF && k != '\n' && i < size; i++)
    {
      buff[i] = k;
      k = getchar ();

      if (k == EOF && !feof (stdin))
        {
          return NULL;
        }
    }

  buff[i] = '\0';

  return buff;
}

char **
ParseParamStr (char *str)
{
  char **args = (char **)malloc (sizeof (char *));
  char *lexeme = strtok (str, " ");
  unsigned int i = 0;

  for (unsigned int i = 0; lexeme; i++)
    {
      args = (char **)realloc (args, sizeof (char *) * (i + 1));
      args[i] = (char *)malloc (sizeof (char) * strlen (lexeme));
      strcpy (args[i], lexeme);
      lexeme = strtok (NULL, " ");
    }

  return args;
}

int
main (void)
{
  char buff[64];
  char dir[] = "/bin/";
  char *lexeme;
  char **args;
  int fd[2];

  while (1)
    {
      printf (">:");
      sgets (buff, 64);
      lexeme = strtok (buff, "|");
      for (unsigned int i = 0; lexeme; i++)
        {
          pipe (fd);
          pid_t process = fork ();
          if (process)
            {
              wait ();
              lexeme = strtok (NULL, "|");
              if (!lexeme)
                {
                  break;
                }
              pid_t process_1 = fork ();
              if (process_1)
                {
                  wait ();
                  lexeme = strtok (NULL, "|");
                }
              else
                {
                  args = ParseParamStr (lexeme);
                  dup2 (fd[0], 0);
                  if (execvp (strcat (dir, args[0]), args) == -1)
                    {
                      printf ("Command not found!\n");
                      exit (EXIT_FAILURE);
                    }
                }
            }
          else
            {
              args = ParseParamStr (lexeme);
              dup2 (fd[1], 1);
              if (execvp (strcat (dir, args[0]), args) == -1)
                {
                  printf ("Command not found!\n");
                  exit (EXIT_FAILURE);
                }
            }
        }
    }

  exit (EXIT_SUCCESS);
}
