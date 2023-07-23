#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
int i = 0;

struct sprav
{
  char name[MAX];
  char surname[MAX];
  int number;
};

struct sprav kniga[1000];

int
add ()
{
  char c;
  while ((c = getchar ()) != '\n' && c != EOF)
    /* discard */;
  printf ("ENTER NAME (30 chars max):\n");
  fgets (kniga[i].name, MAX, stdin);
  printf ("ENTER SURNAME (30 chars max):\n");
  fgets (kniga[i].surname, MAX, stdin);
  printf ("ENTER PHONE NUMBER:\n"); // if user uses anything other than numbers
                                    // programm is doomed
  scanf ("%d", &kniga[i].number);
  printf ("\nadded to i=%d\n   %s   %s   %d\n\n", i, kniga[i].name,
          kniga[i].surname, kniga[i].number);
  i++;
  return 0;
}

void
del ()
{
  int j;
  printf ("ENTER NUMBER :\n"); // if user uses anything other than numbers
                               // programm is doomed
  scanf ("%d", &j);
  for (j; j < i; j++)
    {
      strcpy (kniga[j].name, kniga[j + 1].name);
      strcpy (kniga[j].surname, kniga[j + 1].surname);
      kniga[j].number = kniga[j + 1].number;
    }
  i--;
}

void
search ()
{
  int x;
  int j, fl = 1;
  printf ("CHOOSE SEARCH KEY\n1 - NUMBER\n2 - NAME\n3 - SURNAME\n4 - "
          "NUMBER\n5 - EXIT\n");
  scanf ("%d", &x);
  char key[MAX];
  switch (x)
    {
    case 1:
      {
        printf ("ENTER NUMBER :\n"); // if user uses anything other than
                                     // numbers programm is doomed
        scanf ("%d", &j);
        printf ("\n%2d %30s%33s%32d", j, kniga[j].name, kniga[j].surname,
                kniga[j].number);
        printf ("\n            FOUND\n\n");
        break;
      }
    case 2:
      {
        char c;
        while ((c = getchar ()) != '\n' && c != EOF)
          /* discard */;
        printf ("ENTER NAME (30 chars max) :\n");
        fgets (key, MAX, stdin);
        for (j = 0; j < i; j++)
          {
            if (!strcmp (key, kniga[j].name))
              {
                printf ("\n%2d %30s%33s%32d", j, kniga[j].name,
                        kniga[j].surname, kniga[j].number);
                printf ("\n            FOUND\n\n");
                fl = 0;
              }
          }
        if (fl)
          printf ("\n        NOT FOUND\n\n");
        break;
      }
    case 3:
      {
        char c;
        while ((c = getchar ()) != '\n' && c != EOF)
          /* discard */;
        printf ("ENTER SURNAME (30 chars max):\n");
        fgets (key, MAX, stdin);
        for (j = 0; j < i; j++)
          {
            if (!strcmp (key, kniga[j].surname))
              {
                printf ("\n%2d %30s%33s%32d", j, kniga[j].name,
                        kniga[j].surname, kniga[j].number);
                printf ("\n            FOUND\n\n");
                fl = 0;
              }
          }
        if (fl)
          printf ("\n        NOT FOUND\n\n");
        break;
      }
    case 4:
      {
        printf ("ENTER PHONE NUMBER :\n"); // if user uses anything other than
                                           // numbers programm is doomed
        scanf ("%d", &x);
        for (j = 0; j < i; j++)
          {
            if (kniga[j].number == x)
              {
                printf ("\n%2d %30s%33s%32d", j, kniga[j].name,
                        kniga[j].surname, kniga[j].number);
                printf ("\n            FOUND\n\n");
                fl = 0;
              }
          }
        if (fl)
          printf ("\n        NOT FOUND\n\n");
        break;
      }
    default:
      {
        return;
      }
    }
}

int
print1 ()
{
  printf ("PRINTING WHOLE BOOK:\n");
  for (int j = 0; j < i; j++)
    printf ("\n%2d %30s%33s%32d", j, kniga[j].name, kniga[j].surname,
            kniga[j].number);
  printf ("\n            END\n\n");
  return 0;
}

int
main ()
{
  int x;
  int i = 0;
  while (1)
    {
      printf ("1 - ADD\n2 - DELETE\n3 - SEARCH\n4 - PRINT\nELSE = "
              "EXIT\n\nENTER OPTION :\n");
      scanf ("%d", &x);
      if (x == 1)
        add ();
      else if (x == 2)
        del ();
      else if (x == 3)
        search ();
      else if (x == 4)
        print1 ();
      else
        return 0;
    }
}
