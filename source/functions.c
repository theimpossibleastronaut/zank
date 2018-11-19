/*
 * functions.c
 *
 * Copyright 2012-2018 Andy Alt <andyqwerty@users.sourceforge.net>
 *
 * https://github.com/theimpossibleastronaut/Zank/wiki
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

#include <unistd.h>
#include "functions.h"
#include "utils.h"

bool
accuse (st_player_data *player)
{
  extern st_map map;
  if (map.cell[player->cell].object[0] == indicted_politician)
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
    player->health = player->health + 5;
    t = rand () % 3;

    if (!t)
    {
      printw
        ("You have been blackmailed by an ally of the politican! (-5 hp)\n");
      player->health = player->health - 5;
    }
  }
  else
  {
    printw ("A grand jury has found him innocent,\n");
    printw ("but after the stress of the trial\n");
    printw ("he chooses early retirement.\n");
    printw ("\nYou're plagued with a guilty conscience. (-5 HP)\n");
    player->health = player->health - 5;
  }

  map.cell[player->cell].object[0] = indicted_politician;
  return 1;
}

void
showitems (st_objects * object)
{

  printw ("Your inventory:\n");
  if (object->swords || object->documents || object->rings || object->seeds)
  {
    printw ("Swords: %d\n", object->swords);
    printw ("Incriminating Documents: %d\n", object->documents);
    printw ("Magic Rings: %d\n", object->rings);
    printw ("Seeds: %d\n", object->seeds);
  }

  else
    printw ("You're not carrying anything");

  printw ("\n");

}

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
showMap (st_player_data *player)
{
  extern st_map map;
  int column, row;
  short print_row = 2;
  int ctr = 0;
  for (column = X - 1; column >= 0; column--)
  {
    mvprintw (print_row++, 64, "");

    for (row = 0; row < Y; row++)
    {
      if (ctr == player->cell)
        printw ("@");
      else if (map.cell[ctr].is_explored == 1)
      {
        if (map.cell[ctr].object[0] == politician)
          printw ("p");
        else if (map.cell[ctr].object[0] == Wall)
          printw ("W");
        else if (map.cell[ctr].object[0] == Lake)
          printw ("L");
        else if (map.cell[ctr].object[0] == Grapevine)
          printw ("G");
        else
          printw ("X");
      }
      else
        printw ("*");

      ctr++;
    }
  }
}

void
prompt (st_player_data *player, short pCtr, short iCtr)
{
  extern st_map map;
  mvprintw (22, 0,
            "\n(%d,%d) (politicians left to retire: %d) (HP: %d) (i,q[uit]) (e,w,n,s)? ",
            map.cell[player->cell].pos_y, map.cell[player->cell].pos_x, pCtr - iCtr, player->health);
}

bool
borderPatrol (st_player_data *player)
{
  printw
    ("\nYou were attacked while trying to invade the neighboring kingdom (-2 hp)\n");
  player->health = player->health - 2;
  return 1;
}

void change_pos(st_player_data *player, const char c, int which)
{
  extern const st_direction direction[];
  extern const int sfd;
  extern const bool is_client;
  char buf[1024];
  player->cell = player->cell + direction[which].offset;

  if (is_client)
  {
    char y_str_pos[4];
    char x_str_pos[4];
    extern st_map map;
    itoa (map.cell[player->cell].pos_y, y_str_pos);
    itoa (map.cell[player->cell].pos_x, x_str_pos);
    int len = snprintf (buf, BUF_SIZE, "pos = %s,%s", y_str_pos, x_str_pos);
    len++;
    if (write (sfd, buf, len) != len)
    {
      fprintf (stderr, "partial/failed write\n");
      exit (EXIT_FAILURE);
    }
  }

  /*
  len = strlen (test_string) + 1;
  if (write (sfd, test_string, len) != len)
  {
    fprintf (stderr, "partial/failed write\n");
    exit (EXIT_FAILURE);
  } */


  printw ("%s\n", direction[which].str_which);

  return;
}


