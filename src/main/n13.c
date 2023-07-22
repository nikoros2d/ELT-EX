#include <curses.h>    //ncurses
#include <dirent.h>    //scandir
#include <signal.h>    //ncurses
#include <stdlib.h>    //ncurses
#include <string.h>    //maybe later will resolve warnings
#include <sys/ioctl.h> //signal
#include <sys/stat.h>  //stat
#include <termios.h> //signal //honestly i have no idea why this suddenly started bombarding with warnings, still works just fine
#define MAXBUF 2000

WINDOW *wnd;
WINDOW *wnd1;
WINDOW *subwnd;
WINDOW *subwnd1;
// WINDOW * TEXT//this may be implemented in the future as copy/del commands
// may be required
WINDOW *help;
void redacting ();
void
sig_winch (int signo)
{
  struct winsize size;
  ioctl (fileno (stdout), TIOCGWINSZ, (char *)&size);
  resizeterm (size.ws_row, size.ws_col);
}

void
moving ()
{
  wmove (wnd1, 0, 0);
  noecho ();
  int ch;
  keypad (subwnd1, TRUE);
  keypad (wnd1, TRUE);
  char buffer[MAXBUF];
  char pathbuf[MAXBUF];
  getcwd (pathbuf, MAXBUF);
  char pathbuf1[MAXBUF];
  getcwd (pathbuf1, MAXBUF);
  int i = 0, j;
  int g = 0;
  struct stat x;
  // stat(".",&x);
  // printf("%d\n",x.st_mode);
  // if(S_ISDIR(x.st_mode)){
  struct dirent **namelist;
  struct dirent **subnamelist;
  int n;
  n = scandir (".", &namelist, 0, alphasort);
  n = scandir (".", &subnamelist, 0, alphasort);
  // printf("%d\n",n);
  if (n < 0)
    perror ("scandir");
  else
    {
      for (j = 2; j < n; j++)
        {
          wprintw (subwnd1, "%s\n", subnamelist[j]->d_name); //
          wprintw (wnd1, "%s\n", namelist[j]->d_name);
          wrefresh (wnd1);
          wrefresh (subwnd1);

          /// free(namelist[i]);
        }
      // free(namelist);
    } //}
  wmove (wnd1, 0, 0);
  while (1)
    {

      while (1)
        {
          ch = wgetch (wnd1);
          if (ch == KEY_UP)
            {
              if (i >= 0)
                {
                  i--;
                  wmove (wnd1, i, 0);
                }
            } // up
          if (ch == KEY_DOWN)
            {
              if (i <= 21)
                {
                  i++;
                  wmove (wnd1, i, 0);
                }
            } // down
          if (ch == KEY_RIGHT)
            {
              strcat (pathbuf, "/");
              strcat (pathbuf, namelist[i + 2]->d_name);

              stat (pathbuf, &x);
              if (S_ISDIR (x.st_mode))
                {
                  n = scandir (pathbuf, &namelist, 0, alphasort);
                  if (n < 0)
                    perror ("scandir");
                  else
                    {
                      wclear (wnd1);
                      for (j = 2; j < n; j++)
                        {
                          wprintw (wnd1, "%s\n", namelist[j]->d_name);
                          wrefresh (wnd1);
                        }
                      wmove (wnd1, i, 0);
                    }
                }
              else
                {
                  g = 0;
                  while (pathbuf[g] != NULL)
                    g++;
                  while (pathbuf[g] != '/')
                    {
                      pathbuf[g] = NULL;
                      g--;
                    }
                  pathbuf[g] = NULL;
                  if (S_ISREG (x.st_mode))
                    {

                      ;
                    }
                }
            }
          // right in file
          if (ch == KEY_LEFT)
            {
              g = 0;
              while (pathbuf[g] != NULL)
                g++;
              while (pathbuf[g] != '/')
                {
                  pathbuf[g] = NULL;
                  g--;
                }
              pathbuf[g] = NULL;
              n = scandir (pathbuf, &namelist, 0, alphasort);
              if (n < 0)
                perror ("scandir");
              else
                {
                  wclear (wnd1);
                  for (j = 2; j < n; j++)
                    {
                      wprintw (wnd1, "%s\n", namelist[j]->d_name);
                      wrefresh (wnd1);
                    }
                  wmove (wnd1, 0, 0);
                }
            }
          if (ch == 9)
            {
              wmove (subwnd1, i, 0);
              break;
            } // tab
          if (ch == 27)
            {
              return;
            } // esc
        }

      while (1)
        {
          ch = wgetch (subwnd1);
          if (ch == KEY_UP)
            {
              if (i >= 0)
                {
                  i--;
                  wmove (subwnd1, i, 0);
                }
            } // up
          if (ch == KEY_DOWN)
            {
              if (i <= 21)
                {
                  i++;
                  wmove (subwnd1, i, 0);
                }
            } // down
          if (ch == KEY_RIGHT)
            {
              strcat (pathbuf1, "/");
              strcat (pathbuf1, subnamelist[i + 2]->d_name);

              stat (pathbuf1, &x);
              if (S_ISDIR (x.st_mode))
                {
                  n = scandir (pathbuf1, &subnamelist, 0, alphasort);
                  if (n < 0)
                    perror ("scandir");
                  else
                    {
                      wclear (subwnd1);
                      for (j = 2; j < n; j++)
                        {
                          wprintw (subwnd1, "%s\n", subnamelist[j]->d_name);
                          wrefresh (subwnd1);
                        }
                      wmove (subwnd1, i, 0);
                    }
                }
              else
                {
                  g = 0;
                  while (pathbuf1[g] != NULL)
                    g++;
                  while (pathbuf1[g] != '/')
                    {
                      pathbuf1[g] = NULL;
                      g--;
                    }
                  pathbuf1[g] = NULL;
                  if (S_ISREG (x.st_mode))
                    {

                      ;
                    }
                }
            }
          // right in file
          if (ch == KEY_LEFT)
            {
              g = 0;
              while (pathbuf1[g] != NULL)
                g++;
              while (pathbuf1[g] != '/')
                {
                  pathbuf1[g] = NULL;
                  g--;
                }
              pathbuf1[g] = NULL;
              n = scandir (pathbuf1, &subnamelist, 0, alphasort);
              if (n < 0)
                perror ("scandir");
              else
                {
                  wclear (subwnd1);
                  for (j = 2; j < n; j++)
                    {
                      wprintw (subwnd1, "%s\n", subnamelist[j]->d_name);
                      wrefresh (subwnd1);
                    }
                  wmove (subwnd1, 0, 0);
                }
            }
          if (ch == 9)
            {
              wmove (wnd1, i, 0);
              break;
            } // tab
          if (ch == 27)
            {
              return;
            } // esc
        }
    }
}

int
main (int argc, char **argv)
{
  initscr ();
  start_color ();
  signal (SIGWINCH, sig_winch);
  cbreak ();
  refresh ();
  init_pair (1, COLOR_BLACK, COLOR_BLUE);
  help = newwin (1, 80, 23, 0);
  wprintw (help, "      <,>,^,v to traverse          TAB to SWAP            "
                 "ESC to exit    ");
  wrefresh (help);
  wnd = newwin (23, 40, 0, 0);
  subwnd = newwin (23, 40, 0, 40);
  wnd1 = derwin (wnd, 21, 38, 1, 1);
  subwnd1 = derwin (subwnd, 21, 38, 1, 1);
  box (wnd, '|', '-');
  box (subwnd, '|', '-');
  wbkgd (wnd1, COLOR_PAIR (1));
  wbkgd (subwnd1, COLOR_PAIR (1));
  wrefresh (wnd);
  wrefresh (subwnd);
  wrefresh (wnd1);
  wrefresh (subwnd1);

  moving ();

  // getch();
  delwin (subwnd);
  delwin (wnd);
  delwin (help);
  endwin ();
  exit (EXIT_SUCCESS);
}
