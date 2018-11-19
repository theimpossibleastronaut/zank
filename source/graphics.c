#include <stdio.h>
#include "graphics.h"

/* On linux and mac, only <ncurses.h> is needed, but when using */
/* MinGW on Windows, the header can't be found unless this */
/* path is used */
/*
 * FIXME: It would be better to put this conditional include in CMakeList.txt
 *
 */
#ifdef _WIN32
  #include <ncurses/ncurses.h>
#else
  #include <ncurses.h>
#endif

void
tree (void)
{
  start_color ();
  init_pair (1, COLOR_GREEN, COLOR_BLACK);
  init_pair (2, COLOR_MAGENTA, COLOR_BLACK);
  attron (COLOR_PAIR (1));
  printw ("  oOOOOo\n");
  printw (" oOOOOOOo\n");
  printw ("oOOOOOOOOo\n");
  printw (" oOOOOOOo\n");
  printw ("  OOOOo\n");
  attroff (COLOR_PAIR (1));
  attron (COLOR_PAIR (2));
  printw ("    II\n");
  printw ("    II\n");
  printw ("    II\n");
  printw ("    II\n");
  printw ("    II\n");
  printw ("   /xx\\\n");
  attroff (COLOR_PAIR (2));
}


void
wall (void)
{
  start_color ();
  init_pair (1, COLOR_RED, COLOR_WHITE);
  attron (COLOR_PAIR (1));
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  printw ("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
  printw ("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  attroff (COLOR_PAIR (1));
  printw ("\n");
}

void
lake (void)
{
  start_color ();
  init_pair (1, COLOR_WHITE, COLOR_BLUE);
  attron (COLOR_PAIR (1));
  printw ("            \n");
  printw ("              \n");
  printw ("                  \n");
  printw ("                    \n");
  printw ("                     \n");
  printw ("                    \n");
  printw ("                  \n");
  printw ("                \n");
  printw ("             \n");
  printw ("          \n");
  attroff (COLOR_PAIR (1));
  printw ("\n");
}
