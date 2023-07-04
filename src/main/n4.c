#include <stdio.h>
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

void
add ()
{
  printf ("ENTER NAME (30 chars max) >");
  fgets (kniga[i].name, MAX, stdin);
  fflush (stdin);
  printf ("ENTER SURNAME (30 chars max) >");
  fgets (kniga[i].surname, MAX, stdin);
  fflush (stdin);
  printf ("ENTER PHONE NUMBER >"); // if user uses anything other than numbers
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
  printf ("ENTER NUMBER >"); // if user uses anything other than numbers
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
  int x, j, fl = 1;
  printf ("CHOOSE SEARCH KEY\n1 - NUMBER\n2 - NAME\n3 - SURNAME\n4 - "
          "NUMBER\n5 - EXIT\n");
  scanf ("%d", &x);
  fflush (stdin);
  char key[MAX];
  switch (x)
    {
    case 1:
      {
        printf ("ENTER NUMBER >"); // if user uses anything other than numbers
                                   // programm is doomed
        scanf ("%d", &j);
        printf ("\n%2d %30s%33s%32d", j, kniga[j].name, kniga[j].surname,
                kniga[j].number);
        printf ("\n            FOUND\n\n");
        break;
      }
    case 2:
      {
        printf ("ENTER NAME (30 chars max) >");
        fgets (key, MAX, stdin);
        fflush (stdin);
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
        printf ("ENTER SURNAME (30 chars max) >");
        fgets (key, MAX, stdin);
        fflush (stdin);
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
        printf ("ENTER PHONE NUMBER >"); // if user uses anything other than
                                         // numbers programm is doomed
        scanf ("%d", &x);
        fflush (stdin);
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

void
print1 ()
{
  printf ("PRINTING WHOLE BOOK");
  for (int j = 0; j < i; j++)
    printf ("\n%2d %30s%33s%32d", j, kniga[j].name, kniga[j].surname,
            kniga[j].number);
  printf ("\n            END\n\n");
}

int
main ()
{
  int x, i = 0;
  while (1)
    {
      printf ("1 - ADD\n2 - DELETE\n3 - SEARCH\n4 - PRINT\nELSE = "
              "EXIT\n\nENTER OPTION >");
      scanf ("%d", &x);
      fflush (stdin);
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
            return 0;
          }
        }
    }
}
