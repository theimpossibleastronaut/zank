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
  printw ("\
  oOOOOo\n\
 oOOOOOOo\n\
oOOOOOOOOo\n\
 oOOOOOOo\n\
  OOOOOo\n");
attroff (COLOR_PAIR (1));
attron (COLOR_PAIR (2));
  printw ("\
    II\n\
    II\n\
    II\n\
    II\n\
    II\n\
   /xx\\\n");
  attroff (COLOR_PAIR (2));
}


void
wall (void)
{
  start_color ();
  init_pair (1, COLOR_RED, COLOR_WHITE);
  attron (COLOR_PAIR (1));
  printw ("\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n\
HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n\
EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
  attroff (COLOR_PAIR (1));
  printw ("\n");
}

void
lake (void)
{
  start_color ();
  init_pair (1, COLOR_WHITE, COLOR_BLUE);
  attron (COLOR_PAIR (1));
  printw ("\
            \n\
              \n\
                  \n\
                    \n\
                     \n\
                    \n\
                  \n\
                \n\
             \n\
          \n");
  attroff (COLOR_PAIR (1));
  printw ("\n");
}
