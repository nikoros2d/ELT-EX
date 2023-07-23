#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define MAX 30
int i = 1;

struct sprav
{
  char name[MAX];
  char surname[MAX];
  int number;
};
struct sprav *kniga;

void
add ()
{
  kniga = (struct sprav *)realloc (kniga, sizeof (struct sprav) * (i + 1));
  char c;
  while ((c = getchar ()) != '\n' && c != EOF)
    /* discard */;
  printf ("ENTER NAME (30 chars max) :\n");
  fgets (kniga[i].name, MAX, stdin);
  printf ("ENTER SURNAME (30 chars max) :\n");
  fgets (kniga[i].surname, MAX, stdin);
  printf ("ENTER PHONE NUMBER:\n"); // if user uses anything other than numbers
                                    // programm is doomed
  scanf ("%d", &kniga[i].number);
  printf ("\nadded to i=%d\n   %s   %s   %d\n\n", i, kniga[i].name,
          kniga[i].surname, kniga[i].number);
  i++;
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
  // free (kniga[i]);
  i--;
}

void
search ()
{
  int x, j, fl = 1;
  printf ("CHOOSE SEARCH KEY\n1 - NUMBER\n2 - NAME\n3 - SURNAME\n4 - "
          "NUMBER\n5 - EXIT\n");
  scanf ("%d", &x);
  char key[MAX];
  switch (x)
    {
    case 1:
      {
        printf ("ENTER NUMBER:\n"); // if user uses anything other than numbers
                                    // programm is doomed
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
        for (j = 1; j < i; j++)
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
        for (j = 1; j < i; j++)
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
        for (j = 1; j < i; j++)
          {
            if (kniga[j].number == x)
              {
                printf ("\n%2d %30s%33s%32d\n", j, kniga[j].name,
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

void
print1 ()
{
  printf ("PRINTING WHOLE BOOK:\n");
  for (int j = 1; j < i; j++)
    printf ("\n%2d %30s%33s%32d\n", j, kniga[j].name, kniga[j].surname,
            kniga[j].number);
  printf ("            END\n\n");
}

int
main ()
{
  kniga = (struct sprav *)malloc (sizeof (struct sprav) * 2);
  int x, i = 0;
  while (1)
    {
      printf ("1 - ADD\n2 - DELETE\n3 - SEARCH\n4 - PRINT\nELSE = "
              "EXIT\n\nENTER OPTION:\n");
      scanf ("%d", &x);
      switch (x)
        {
        case 1:
          {
            add ();
            break;
          }
        case 2:
          {
            del ();
            break;
          }
        case 3:
          {
            search ();
            break;
          }
        case 4:
          {
            print1 ();
            break;
          }
        default:
          {
            free (kniga);
            return 0;
          }
        }
    }
}
