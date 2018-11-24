/** \file functions.c
 */
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
#include "player.h"
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
showitems (st_player_data *player)
{
  printw ("Your inventory:\n");

  printw ("Swords: %d\n", player->inventory.swords);
  printw ("Incriminating Documents: %d\n", player->inventory.documents);
  printw ("Magic Rings: %d\n", player->inventory.rings);
  printw ("Seeds: %d\n", player->inventory.seeds);

  printw ("\n");
  printw (" = Financial Portfolio =\n");
  printw ("Diamond Mines: %d\n", player->inventory.diamond_mine);
  printw ("Diamonds: %.2f\n", player->inventory.diamonds);

  printw ("\n");

  printw (" = Military =\n");
  printw ("Barracks: %d\n", player->inventory.barracks);
  printw ("Pawns: %d\n", player->army.pawn.attribute.count);
  printw ("Knights: %d\n", player->army.knight.attribute.count);

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
            "\n(%d,%d) (politicians left to retire: %d) (HP: %d) (h,i,c,g,q[uit]) (e,w,n,s)? ",
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

/** Run when a player selects a direction key. This function uses the
 * \ref direction struct and it's corresponding enum field in \ref zank.h to determine
 * the location of the player's cell.
 * @param[in,out] player
 * @param[in] c
 * @param[in] which
 * @return void
 */
void change_pos(st_player_data *player, const char c, int which)
{
  extern const st_direction direction[];
  extern const int sfd;
  extern const bool is_client;
  player->cell = player->cell + direction[which].offset;

  player->inventory.diamonds += (DIAMONDS_PER_TURN * player->inventory.diamond_mine);
  player->inventory.diamonds += player->inventory.diamonds * INTEREST;

  if (is_client)
  {
    char cell_num[BUF_SIZE];
    extern st_map map;
    itoa (player->cell, cell_num);
    char buf[BUF_SIZE];
    int len = snprintf (buf, BUF_SIZE, "cell = %s", cell_num);
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

void
init_map_cell_positions ()
{
  extern st_map map;
  int pos_x, pos_y;
  int num = 0;
  for (pos_x = 0; pos_x < X; pos_x++)
    for (pos_y = 0; pos_y < Y; pos_y++)
    {
      map.cell[num].pos_x = pos_x;
      map.cell[num].pos_y = pos_y;
      num++;
    }
}


