/*
 * main.c
 *
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

st_direction direction[] = {
  { "West", -1 },
  { "East", 1 },
  { "North", 1 },
  { "South", -1 }
};

/*
 *  socket file descriptor for network communication
 */
int sfd = 0;

bool is_client = 0;
bool is_server = 0;

int
main (int argc, char* const *argv)
{
  const char *const short_options = "cshv";

  const struct option long_options[] = {
    {"connect", 0, NULL, 'c'},
    {"server", 0, NULL, 's'},
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {NULL, 0, NULL, 0}
  };

  int next_option = 0;

  do
  {
    next_option = getopt_long (argc, argv, short_options, long_options, NULL);

    switch ((char)next_option)
    {
      case 'c':
        sfd = zank_connect (argv);
        is_client = 1;
        break;
      case 's':
        is_server = 1;
        break;
      case 'h':                /* -h */
        display_help ();
        return 0;
      case 'v':
        display_version ();
        return 0;
      default:
        break;
    }
  } while (next_option != -1);

  if (is_server && is_client)
  {
    fprintf (stderr, "Zank cannot be a client and server.\n");
    exit (1);
  }

  st_player_data player;

  player.health = 100;
/**
 * Starting position
 */
  player.pos_x = X / 2;
  player.pos_y = Y / 2;

  if (is_server)
    run_server (&player);

  /**
   * NOTE: the order here must match with the object listed in the
   * enum declaration in Zank.h
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
    "a grapevine"
  };

  creature creatures[] = {

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

  int creature_count = ARRAY_SIZE(creatures);

  int which_creature;

  bool flag = 0;

  srand (time (0));

  int randgrape;

/**
 * Generate coordinates for Magic Waterfall
 */
  int rx, ry;
  rx = rand () % X;
  ry = rand () % Y;

  const unsigned short politician_total = X * Y / 6;

/**
 * Initialize map
 */
  unsigned short column, row;
  int politicianCtr = 0;

  map[rx][ry] = MagicWaterfall;

  while (politicianCtr < politician_total)
  {
    int rand_x, rand_y;
    rand_x = rand () % X;
    rand_y = rand () % Y;

    if (map[rand_x][rand_y] != politician &&
        (map[rand_x][rand_y] != MagicWaterfall))
    {
      map[rand_x][rand_y] = politician;
      politicianCtr++;
    }
  }

  objects *object = (objects*)malloc (sizeof (objects));
  if (object == NULL)
  {
    fprintf (stderr, "Error allocating memory.\n");
    exit (EXIT_FAILURE);
  }

  for (column = 0; column < X; column++)
  {
    for (row = 0; row < Y; row++)
    {
      do
      {
        object->pos = rand () % 8;
      }
      while (object->pos == politician);

      if (map[column][row] != politician &&
          map[column][row] != MagicWaterfall)
        map[column][row] = object->pos;
    }
  }

  politicianCtr = politician_total;

  int indictedCtr = 0;

  initscr ();

  printw ("\nZank version %s\n", VERSION);
  printw ("By %s\n", AUTHOR);
  printw ("With code contributions from mzdelong\n");
  refresh ();

  /* prompt(politicianCtr, indictedCtr);
     refresh(); */

  bool Visited[X][Y];
  /**
   * Init Array
   */
  for (column = 0; column < X; column++) {
    for (row = 0; row < Y; row++) {
      Visited[column][row] = 0;
    }
  }

  bool isStarting = 1;

 /**
  * from the ncurses library - needed for cursor key checking
  */
  keypad (stdscr, TRUE);

  short c = -999;

  while (c != EOF && player.health > 0 && politicianCtr != indictedCtr && c != 'q')
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

    int t;
    t = rand () % 2;
    flag = 0;

    /* This way caps lock doesn't matter */
    if (isupper (c))
      c = tolower (c);

    switch (c)
    {
    case KEY_UP:
      c = 'n';
      break;

    case KEY_DOWN:
      c = 's';
      break;

    case KEY_LEFT:
      c = 'w';
      break;

    case KEY_RIGHT:
      c = 'e';
      break;

    default:
      break;
    }

    switch (c)
    {
    case 'e':
      if (player.pos_y < Y - 1)
        change_pos(&player, 'y', EAST);
      else
        flag = borderPatrol (&player);
      break;

    case 'w':
      if (player.pos_y > 0)
        change_pos(&player, 'y', WEST);
      else
        flag = borderPatrol (&player);
      break;

    case 's':
      if (player.pos_x > 0)
        change_pos (&player, 'x', SOUTH);
      else
        flag = borderPatrol (&player);
      break;

    case 'n':
      if (player.pos_x < X - 1)
        change_pos (&player, 'x', NORTH);
      else
        flag = borderPatrol (&player);
      break;

    case 'i':
      showitems (object);
      flag = 1;
      break;

    case 'h':
      printw ("Help and Commands:\n");
      printw
        ("\tGo in direction: e = East ; w = West ; n = North ; s = South\n");
      printw ("\t\t(Or use the left/right/up/down cursor keys\n");
      printw ("\ti = show inventory\n");
      printw ("\tq = quit game\n");

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
      Visited[player.pos_x][player.pos_y] = 1;

      object->pos = map[player.pos_x][player.pos_y];

      printw ("\nYou see %s\n", mapObject[object->pos]);

      bool acquire = 0;
      switch (object->pos)
      {
      case an_incriminating_document:
        acquire = 1;
        object->documents++;
        break;

      case Magic_Ring:
        acquire = 1;
        object->rings++;
        break;

      case Sword:
        acquire = 1;
        object->swords++;
        break;

      default:
        break;
      }

      if (acquire)
      {
        printw ("Acquiring %s\n", mapObject[map[player.pos_x][player.pos_y]]);
        map[player.pos_x][player.pos_y] = Seed;
      }

      printw ("\n");

      switch (object->pos)
      {
      case politician:
        /* locations[foundpolitician][0] = x;
           locations[foundpolitician][1] = y;
           foundpolitician++; */

        if (object->documents)
        {
          if (accuse (&player))
          {
            object->documents--;
            indictedCtr++;
          }
        }
        else if (object->rings)
        {
          if (accuse (&player))
          {
            object->rings--;
            indictedCtr++;
          }
        }
        else if (!object->documents && !object->rings)
          printw
            ("If you had some incriminating documents or magic rings,\nyou'd be able to indict him.\n");
        break;

      case Wall:
        wall ();
        if (t == 1 && object->rings)
        {
          printw ("You ran into a wall and ruined a Magic Ring.\n");
          object->rings--;
        }
        else if (!t && !object->rings)
        {
          printw ("You ran into wall. (-1 hp)\n");
          player.health--;
        }
        break;

      case Lake:
        lake ();
        if (t == 1 && object->documents)
        {
          printw
            ("You fell into the lake and lost an incriminating document.\n");
          object->documents--;
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
        map[player.pos_x][player.pos_y] = Dried_up_Waterfall;
        break;

      case Clearing:
        which_creature = rand () % creature_count;
        if (object->seeds)
        {
          printw ("You plant a seed. You feel better. (+1 hp)\n");
          object->seeds--;
          t = rand () % 4;

          if (t >= 0 && t < 3)
          {
                                        /**
           * map[x][player.pos_y] will equal one of the items for the enum declaration
           * item 5-7
           */
            map[player.pos_x][player.pos_y] = t + an_incriminating_document;
          }
          else
            map[player.pos_x][player.pos_y] = Grapevine;
        }

        t = rand () % 4;
        if (t < 3 && !object->swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\n(-%u HP)\n\n", creatures[which_creature].name,
                  creatures[which_creature].strength);
          player.health = player.health - creatures[which_creature].strength;
        }
        else if (t < 3 && object->swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your sword\n", creatures[which_creature].name);
          printw
            ("protected you. That sword is now broken and you discard it.\n\n");
          object->swords--;
        }
        else if (t < 3 && object->rings)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your Magic\n", creatures[which_creature].name);
          printw
            ("Ring protected you. That ring is now broken and you discard it.\n\n");
          object->rings--;
        }
        break;

      case Tree:
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
        object->seeds++;
        map[player.pos_x][player.pos_y] = Clearing;
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
    showMap (&player, Visited);
    refresh ();
  }

  clear ();

  printw ("\nOut of %d politicians, you have retired %d of them.\n",
          politicianCtr, indictedCtr);
  printw ("Your health is %d\n\n", player.health);

  showitems (object);

  printw ("\nEnter 'x' to exit\n");
  refresh ();
  while ((c = getch ()) != EOF && c != 'x' && c != 'X')
  {
  }
  endwin ();

  free (object);

  return 0;
}
