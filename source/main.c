/** \file main.c
 */
/*
 * Copyright 2012-2018 Andy Alt <andy400-dev@yahoo.com>
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

#include <getopt.h>
#include "main.h"
#include "functions.h"
#include "usage.h"
#include "net.h"
#include "graphics.h"
#include "player.h"
#include "military.h"
#include "utils.h"

char guid[GUID_LEN];

st_map map;

/** The strings are printed on the screen after the player moves in that
 * direction. This is primarily used by \ref change_pos()
 */
st_direction direction[] = {
  {"West", -1},
  {"East", 1},
  {"North", -Y},
  {"South", Y }
};

/*
 *  socket file descriptor for network communication
 */
int sfd = 0;

bool is_client = 0;
bool is_server = 0;

int
main (int argc, char *const *argv)
{
  char *zank_host = NULL;

  const char *const short_options = "c:shv";

  const struct option long_options[] = {
    {"connect", 1, NULL, 'c'},
    {"server", 0, NULL, 's'},
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {NULL, 0, NULL, 0}
  };

  int next_option = 0;

  do
  {
    next_option = getopt_long (argc, argv, short_options, long_options, NULL);

    switch ((char) next_option)
    {
    case 'c':
      zank_host = optarg;
      sfd = zank_connect (argv, zank_host);
      is_client = 1;
      break;
    case 's':
      is_server = 1;
      break;
    case 'h':                  /* -h */
      display_help ();
      return 0;
    case 'v':
      display_version ();
      return 0;
    default:
      break;
    }
  }
  while (next_option != -1);

  if (is_server && is_client)
  {
    fprintf (stderr, "Zank cannot be a client and server.\n");
    exit (1);
  }

  /** The random number generator is seeded with the value returned
   * by time(), in this case, the number of seconds since 1970.
   */
  srand (time (NULL));

  generate_guid (guid);

  st_player_data player;

  player.health = 100;

/**
 * A player is assigned a starting position.
 */
  player.cell = MAP_SIZE / 2;

  if (is_server)
  {

    init_map_cell_positions ();
    run_server ();
  }

  /** \page code Detailed Code Information
   * \section map_objects Map Objects
   * The order of the objects in string form
   * here must match with the object listed in the
   * enum declaration in Zank.h \ref map_objects
   */
  char *mapObject[] = {
    "a tree",
    "a lake",
    "a clearing",
    "a politician",
    "a wall",
    "an incriminating document",
    "a sword",
    "a magic ring",
    "a retired politician",
    "a Magic Waterfall",
    "a dried up waterfall",
    "a magic seed",
    "a grapevine",
    "a diamond mine",
    "a barracks"
  };

  st_creature creatures[] = {

    {"an evil gorilla", 6},
    {"a deranged vulture", 5},
    {"Angry Smurf(tm)", 2},
    {"a religious fanatic", 3},
    {"an imaginary enemy", 1},
    {"Emperor Killewe", 7},
    {"meddling kids in a van", 10},
    {"everyone you ever wronged", 15},
    {"your worst nightmare", 20},
    {"a starving artist", 1},
    {"an innocent-looking rabbit", 1},
    {"your own insecurities", 7},
    {"your evil twin", 4},
    {"a telemarketer", 3},
    {"a nasty band of evil cannibalistic cave dwellers", 12},
    {"political repercussions", 6},
    {"a misguided priest", 2},
    {"a lawman who has to feed his family", 3},
    {"an arrogant pop star", 2},
    {"the ogre next door", 4},
    {"a lightning bolt sent by Zeus", 15},
    {"an unusually agressive gerbil", 3},
    {"a sense of strangeness", 1},
    {"a guilty conscience", 4},
    {"hallucinations", 6}
  };

  int creature_count = ARRAY_SIZE (creatures);

  int which_creature;

  int randgrape;

/**
 * A number between 0 and 100 is generated to determine the position of
 * the magic waterfall, and then the cell is assigned the value corresponding
 * to the magic waterfall.
 */
  int waterfall_pos = rand () % MAP_SIZE;

  map.cell[waterfall_pos].object[0] = MagicWaterfall;

/** \page code How politicians are placed
 * The total number of politicians are determined by the MAP_SIZE
 * divided by 6. Within a loop, a random number between 0 and MAP_SIZE
 * is generated. The politician is placed into the corresponding cell.
 * The code loops until politician_total is reached. During each iteration
 * of the loop, the cell is checked to make sure it's not already occupied
 * by a politician.
 *
 */
  init_map_cell_positions ();
  const unsigned short politician_total = MAP_SIZE / 6;
  int politicianCtr = 0;

  while (politicianCtr < politician_total)
  {
    int politician_pos = rand () % MAP_SIZE;
    if (map.cell[politician_pos].object[0] != politician &&
        (map.cell[politician_pos].object[0] != MagicWaterfall))
    {
      map.cell[politician_pos].object[0] = politician;
      politicianCtr++;
    }
  }

  player.inventory.documents = 0;
  player.inventory.rings = 0;
  player.inventory.seeds = 0;
  player.inventory.swords = 0;
  player.inventory.diamond_mine = 1;
  player.inventory.diamonds = 0;
  player.inventory.barracks = 0;
  player.army.pawn.attribute.count = 0;
  player.army.knight.attribute.count = 0;

  int ctr;
  int object_num;
  for (ctr = 0; ctr < MAP_SIZE; ctr++)
  {
    do
    {
      object_num = rand () % 8;
    }
    while (object_num == politician);

    if (map.cell[ctr].object[0] != politician &&
        map.cell[ctr].object[0] != MagicWaterfall)
      map.cell[ctr].object[0] = object_num;
  }

  politicianCtr = politician_total;

  int indictedCtr = 0;

  initscr ();

  printw ("\nZank version %s\n", VERSION);
  printw ("By %s\n", AUTHOR);
  printw ("With code contributions from mzdelong\n");
  refresh ();

  bool isStarting = 1;

  /*
   * from the ncurses library - needed for cursor key checking
   */
  keypad (stdscr, TRUE);

  short c = -999;

  while (c != EOF && player.health > 0 && politicianCtr != indictedCtr
         && c != 'q')
  {
    if (isStarting == 0)
    {
      c = getch ();
      clear ();
    }
    else
    {
      c = 'b';
      isStarting = 0;
    }

    int t = rand () % 2;
    bool flag = 0;

    /* This way caps lock doesn't matter */
    if (isupper (c))
      c = tolower (c);

    /** \page gameplay How to play
     * A user can move East (right), West (left), North (up), South (down)
     * by using the cursor keys or corresponding direction key (e, w, n, s).
     */
    switch (c)
    {
    case KEY_RIGHT:
    case 'e':
      if (map.cell[player.cell].pos_y < Y - 1)
        change_pos (&player, 'y', EAST);
      else
        flag = borderPatrol (&player);
      break;

    case KEY_LEFT:
    case 'w':
      if (map.cell[player.cell].pos_y > 0)
        change_pos (&player, 'y', WEST);
      else
        flag = borderPatrol (&player);
      break;

    case KEY_DOWN:
    case 's':
      if (map.cell[player.cell].pos_x < X - 1)
        change_pos (&player, 'x', SOUTH);
      else
        flag = borderPatrol (&player);
      break;

    case KEY_UP:
    case 'n':
      if (map.cell[player.cell].pos_x > 0)
        change_pos (&player, 'x', NORTH);
      else
        flag = borderPatrol (&player);
      break;

    case 'c':
      construct_barracks (&player);
      flag = 1;
      break;

    case 'g':
      train_units (&player);
      flag = 1;
      break;

    case 'i':
      showitems (&player);
      flag = 1;
      break;

    case 'h':
      printw ("Help and Commands:\n");
      printw
        ("\tGo in direction: e = East ; w = West ; n = North ; s = South\n");
      printw ("\t\t(Or use the left/right/up/down cursor keys\n");
      printw ("\ti = show inventory\n");
      printw ("\tq = quit game\n");
      printw ("\tc = construct barracks\n");
      printw ("\tg = get units\n");

      flag = 1;
      break;

    case 'b':                  /* b)eginning of game */
      break;

    default:
      printw ("That is not a valid direction\n");
      refresh ();
      flag = 1;
      break;
    }

    if (!flag)
    {
      printw ("Diamonds: %.2f\n\n", player.inventory.diamonds);
      map.cell[player.cell].is_explored = 1;

      int object_num = map.cell[player.cell].object[0];

      int object_ctr = 0;
      for (object_ctr = 0; object_ctr < MAX_CELL_OBJECTS; object_ctr++)
      {
        int object_num = map.cell[player.cell].object[object_ctr];
        if (object_num != 0)
          printw ("\nYou see %s\n", mapObject[object_num]);
      }

      bool acquire = 0;
      switch (object_num)
      {
      case an_incriminating_document:
        acquire = 1;
        player.inventory.documents++;
        break;

      case Magic_Ring:
        acquire = 1;
        player.inventory.rings++;
        break;

      case Sword:
        acquire = 1;
        player.inventory.swords++;
        break;

      default:
        break;
      }

      if (acquire)
      {
        printw ("Acquiring %s\n", mapObject[map.cell[player.cell].object[0]]);
        map.cell[player.cell].object[0] = Seed;
      }

      printw ("\n");

      switch (object_num)
      {
      case politician:
        /* locations[foundpolitician][0] = x;
           locations[foundpolitician][1] = y;
           foundpolitician++; */

        if (player.inventory.documents)
        {
          if (accuse (&player))
          {
            player.inventory.documents--;
            indictedCtr++;
          }
        }
        else if (player.inventory.rings)
        {
          if (accuse (&player))
          {
            player.inventory.rings--;
            indictedCtr++;
          }
        }
        else if (!player.inventory.documents && !player.inventory.rings)
          printw
            ("If you had some incriminating documents or magic rings,\nyou'd be able to indict him.\n");
        break;

      case Wall:
        wall ();
        if (t == 1 && player.inventory.rings)
        {
          printw ("You ran into a wall and ruined a Magic Ring.\n");
          player.inventory.rings--;
        }
        else if (!t && !player.inventory.rings)
        {
          printw ("You ran into wall. (-1 hp)\n");
          player.health--;
        }
        break;

      case Lake:
        lake ();
        if (t == 1 && player.inventory.documents)
        {
          printw
            ("You fell into the lake and lost an incriminating document.\n");
          player.inventory.documents--;
        }
        else if (t == 0)
        {
          printw ("You fell into the lake and caught a cold. (-1 hp)\n");
          player.health--;
        }
        else if (t == 1)
        {
          printw
            ("You take a swim, get cleaned up, and feel refreshed. (+2 hp)\n\n");
          player.health = player.health + 2;
        }
        break;

      case MagicWaterfall:
        printw
          ("You swim at the base of the Magic Waterfall and feel much better. (+40 hp)\n");
        player.health = player.health + 40;
        map.cell[player.cell].object[0] = Dried_up_Waterfall;
        break;

      case Clearing:
        which_creature = rand () % creature_count;
        if (player.inventory.seeds)
        {
          printw ("You plant a seed. You feel better. (+1 hp)\n");
          player.inventory.seeds--;
          t = rand () % 4;

          if (t >= 0 && t < 3)
          {
                                        /**
           * map[x][player.pos_y] will equal one of the items for the enum declaration
           * item 5-7
           */
            map.cell[player.cell].object[0] = t + an_incriminating_document;
          }
          else
            map.cell[player.cell].object[0] = Grapevine;
        }

        t = rand () % 4;
        if (t < 3 && !player.inventory.swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\n(-%u HP)\n\n", creatures[which_creature].name,
                  creatures[which_creature].strength);
          player.health = player.health - creatures[which_creature].strength;
        }
        else if (t < 3 && player.inventory.swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your sword\n",
                  creatures[which_creature].name);
          printw
            ("protected you. That sword is now broken and you discard it.\n\n");
          player.inventory.swords--;
        }
        else if (t < 3 && player.inventory.rings)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your Magic\n",
                  creatures[which_creature].name);
          printw
            ("Ring protected you. That ring is now broken and you discard it.\n\n");
          player.inventory.rings--;
        }
        break;

      case TREE:
        tree ();
        if (t == 1)
        {
          printw ("You rest under the tree and feel better (+1 hp)\n");
          player.health++;
        }
        else if (!t)
        {
          printw
            ("A squirrel runs out of the tree,\nbites your ankle,\nand quickly disappears. (-1 hp)\n");
          player.health--;
        }
        break;

      case Seed:
        printw ("Acquiring Seed.\n");
        player.inventory.seeds++;
        map.cell[player.cell].object[0] = Clearing;
        break;

      case Grapevine:
        randgrape = rand () % 4;
        if (randgrape != 2)
        {
          printw ("You eat a grape and feel better. (+1 hp)\n");
          player.health++;
        }
        else
        {
          unsigned short hp_loss = (rand () % 10) + 1;
          printw
            ("The grapes have been poisoned\nand gave you a bad day. (-%u hp)\n",
             hp_loss);
        }
        break;

      default:
        break;
      }
    }
    prompt (&player, politicianCtr, indictedCtr);
    showMap (&player);
    refresh ();
  }

  clear ();

  printw ("\nOut of %d politicians, you have retired %d of them.\n",
          politicianCtr, indictedCtr);
  printw ("Your health is %d\n\n", player.health);

  showitems (&player);

  printw ("\nEnter 'x' to exit\n");
  refresh ();
  while ((c = getch ()) != EOF && c != 'x' && c != 'X')
  {
  }
  endwin ();

  return 0;
}
