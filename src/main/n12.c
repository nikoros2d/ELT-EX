#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#define MAX 100

WINDOW *wnd;
WINDOW *subwnd;
WINDOW *TEXT;

int
sdiv (int i, int d)
{
  int res = 0;
  while (i > d)
    {
      res++;
      i = i - d;
    }
  return res;
}
int
smul (int i, int d)
{
  while (i > d)
    {
      i = i - d;
    }
  return i;
}

void
redacting (char content[])
{
  int i = 0;
  int ch;
  keypad (subwnd, TRUE);
  wmove (subwnd, 0, 0);
  while (1)
    {
      ch = wgetch (subwnd);
      switch (ch)
        {
        case KEY_UP:
          i = i - 80;
          wmove (subwnd, sdiv (i, 80), smul (i, 80));
          break;
        case KEY_DOWN:
          i = i + 80;
          wmove (subwnd, sdiv (i, 80), smul (i, 80));
          break;
        case KEY_LEFT:
          i--;
          wmove (subwnd, sdiv (i, 80), smul (i, 80));
          break;
        case KEY_RIGHT:
          i++;
          wmove (subwnd, sdiv (i, 80), smul (i, 80));
          break;
        case KEY_BACKSPACE:
          return;
        // case '	': return;
        // case 27: wprintw(subwnd,"27 worked!!!");
        default:
          content[i] = ch;
          i++;
          break; // return;
        }
    }
}
void
sig_winch (int signo)
{
  struct winsize size;
  ioctl (fileno (stdout), TIOCGWINSZ, (char *)&size);
  resizeterm (size.ws_row, size.ws_col);
}

void
fileread (FILE *fptr, char content[])
{
  int ch, i;
  while (1)
    {
      while (1)
        {
          move (19, 0);
          wprintw (TEXT, "ENTER FILE PATH> ");
          wgetnstr (TEXT, content, MAX);
          // fptr = fopen (content, "r+");
          fptr = fopen ("t1.txt", "r+");
          if (fptr == NULL)
            {
              wprintw (subwnd, "NO FILE FOUND!!!");
            }
          else
            break;
        }
      fgets (content, 25, fptr);
      wprintw (subwnd, "%s\n", content);
      wrefresh (subwnd);
      while (1)
        {
          wmove (TEXT, 0, 0);
          wprintw (TEXT, "What to do with the file?");
          wrefresh (TEXT);
          ch = wgetch (TEXT);
          if (ch == '	')
            {
              wclear (subwnd);
              wrefresh (subwnd);
              wclear (TEXT);
              wrefresh (TEXT);
              fclose (fptr);
            }
          else if (ch == 'R' || ch == 'r')
            {
              redacting (content);
            }
          else if (ch == 'W' || ch == 'w')
            {
              for (i = 0; i < MAX; i++)
                {
                  if (content[i] == NULL)
                    content[i] = '\0';
                  break; // added \0 as told. this does not alllow any NULL
                         // code be written in
                  i++;
                }
              rewind (fptr);
              fwrite (content, 1, i, fptr);
              wmove (subwnd, 15, 30);
              wprintw (subwnd, "FILE SAVED!!!");
              wrefresh (subwnd);
            }
          else if (ch == 'B' || ch == 'b')
            {
              return;
            }
          else
            {
              wprintw (TEXT, "Error wrong command stage 1");
            }
        }
    }
}
int
main (int argc, char **argv)
{
  FILE *fptr;
  WINDOW *help;

  char content[MAX];
  initscr ();
  start_color ();
  signal (SIGWINCH, sig_winch);
  // cbreak();
  refresh ();
  init_pair (1, COLOR_BLACK, COLOR_WHITE);

  help = newwin (3, 80, 21, 0);
  box (help, '|', '-');
  wmove (help, 1, 1);
  wprintw (help, "<,>,^,v to traverse  BACKSPACE to return  R to redact  W to "
                 "save  B to exit");
  wrefresh (help);
  wnd = newwin (18, 80, 0, 0);
  TEXT = newwin (1, 80, 19, 0);
  wbkgd (TEXT, COLOR_PAIR (1));
  box (wnd, '|', '-');
  wrefresh (wnd);
  subwnd = derwin (wnd, 16, 78, 1, 1);
  wbkgd (subwnd, COLOR_PAIR (1));
  wrefresh (subwnd);

  fileread (fptr, content);
  wmove (TEXT, 0, 0);
  // wgetnstr(subwnd,content,25);
  // move(19,0);
  // printw("%s",content);

  // wprintw(TEXT, "%s\n",content);
  // wrefresh(TEXT);
  getch ();
  delwin (TEXT);
  delwin (subwnd);
  delwin (wnd);
  delwin (help);
  endwin ();
  printf ("%s", content);
  exit (EXIT_SUCCESS);
}
