/*
 * functions.c
 *
 * Copyright 2012, 2016 Andy Alt <andyqwerty@users.sourceforge.net>
 *
 * https://github.com/andy5995/Zank/wiki
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "functions.h"

bool
accuse (void)
{
  if (map[x][y] == indicted_politician)
  {
    printw ("This politician has been indicted recently.\n");
    return 0;
  }

  printw ("You've made a formal charge against the politician!\n");

  int t = rand () % 4;

  if (t)
  {
    printw ("A grand jury has found him guilty.\n");
    printw ("You feel better. (+5 hp)\n\n");
    health = health + 5;
    t = rand () % 3;

    if (!t)
    {
      printw
        ("You have been blackmailed by an ally of the politican! (-5 hp)\n");
      health = health - 5;
    }
  }
  else
  {
    printw ("A grand jury has found him innocent,\n");
    printw ("but after the stress of the trial\n");
    printw ("he chooses early retirement.\n");
    printw ("\nYou're plagued with a guilty conscience. (-5 HP)\n");
    health = health - 5;
  }

  map[x][y] = indicted_politician;
  return 1;
}

void
showitems (void)
{

  printw ("Your inventory:\n");
  if (swords || documents || rings || seeds)
  {
    printw ("Swords: %d\n", swords);
    printw ("Incriminating Documents: %d\n", documents);
    printw ("Magic Rings: %d\n", rings);
    printw ("Seeds: %d\n", seeds);
  }

  else
    printw ("You're not carrying anything");

  printw ("\n");

}

/* void showpoliticians(int foundpolitician) {

	int i;
	printw("\nLocations of politicians:\n");
	printw("%3c %3c\n",'x', 'y');
	printw("-------------------\n");
	for (i = 0; i < foundpolitician; i++)
		printw("%3d %3d\n", locations[i][0], locations[i][1]);

	printw("--- Retired ---\n");
	for (i = 0; i < retiredPoliticians; i++)
		printw("%3d %3d\n", locOfRetiredPoliticians[i][0], locOfRetiredPoliticians[i][1]);
} */

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

void
showMap (bool Visited[X][Y])
{
  int column, row;

  short print_row = 2;

  for (column = X - 1; column >= 0; column--)
  {
    mvprintw (print_row++, 64, "");

    for (row = 0; row < Y; row++)
    {
      if (column == x && row == y)
        printw ("@");
      else if (Visited[column][row] == 1)
      {
        if (map[column][row] == politician)
          printw ("p");
        else if (map[column][row] == Wall)
          printw ("W");
        else if (map[column][row] == Lake)
          printw ("L");
        else if (map[column][row] == Grapevine)
          printw ("G");
        else
          printw ("X");
      }
      else
        printw ("*");
    }
  }

  /* printw("\n"); */
}

void
prompt (short pCtr, short iCtr)
{
  mvprintw (22, 0,
            "\n(%d,%d) (politicians left to retire: %d) (HP: %d) (i,m,q[uit]) (e,w,n,s)? ",
            y, x, pCtr - iCtr, health);
}

bool
borderPatrol (void)
{
  printw
    ("\nYou were attacked while trying to invade the neighboring kingdom (-2 hp)\n");
  health = health - 2;
  return 1;
}
