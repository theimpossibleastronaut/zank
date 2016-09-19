/*
 * main.c
 *
 * Copyright 2012, 2016 Andy Alt <andy400-dev@yahoo.com>
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

#include "main.h"
#include "function_prototypes.h"

int
main (int argc, char **argv)
{
  documents = 0;
  rings = 0;
  swords = 0;
  seeds = 0;
  health = 100;

  int ObjAtCurrentPos;

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

  struct creatures creat[CREATURE_COUNT] = {

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

  int creature;

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

  for (column = 0; column < X; column++)
  {
    for (row = 0; row < Y; row++)
    {
      do
      {
        ObjAtCurrentPos = rand () % 8;
      }
      while (ObjAtCurrentPos == politician);

      if (map[column][row] != politician &&
          map[column][row] != MagicWaterfall)
        map[column][row] = ObjAtCurrentPos;
    }
  }

  politicianCtr = politician_total;

/**
 * Starting position
 */
  x = X / 2;
  y = Y / 2;

  short West = -1;
  short East = 1;
  short North = 1;
  short South = -1;

  int indictedCtr = 0;

  initscr ();

  printw ("\nZank version %s\n", VER);
  printw ("By %s\n", AUTHOR);
  printw ("With code contributions from mzdelong\n");
  refresh ();

  /* prompt(politicianCtr, indictedCtr);
     refresh(); */

  bool Visited[X][Y];
        /**
	 * Init Array
	 */
  for (column = 0; column < X; column++)
    for (row = 0; row < Y; row++)
      Visited[column][row] = 0;

  bool isStarting = 1;

        /**
	* from the ncurses library - needed for cursor key checking
	*/
  keypad (stdscr, TRUE);

  short c;

  while (c != EOF && health > 0 && politicianCtr != indictedCtr && c != 'q')
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
      if (y < Y - 1)
      {
        y = y + East;
        printw ("East\n");
      }
      else
      {
        flag = borderPatrol ();
      }
      break;

    case 'w':
      if (y > 0)
      {
        y = y + West;
        printw ("West\n");
      }
      else
      {
        flag = borderPatrol ();
      }
      break;

    case 's':
      if (x > 0)
      {
        x = x + South;
        printw ("South\n");
      }
      else
      {
        flag = borderPatrol ();
      }
      break;

    case 'n':
      if (x < X - 1)
      {
        x = x + North;
        printw ("North\n");
      }
      else
      {
        flag = borderPatrol ();
      }
      break;

    case 'i':
      showitems ();
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
      Visited[x][y] = 1;

      ObjAtCurrentPos = map[x][y];

      printw ("\nYou see %s\n", mapObject[ObjAtCurrentPos]);

      bool acquire = 0;
      switch (ObjAtCurrentPos)
      {
      case an_incriminating_document:
        acquire = 1;
        documents++;
        break;

      case Magic_Ring:
        acquire = 1;
        rings++;
        break;

      case Sword:
        acquire = 1;
        swords++;
        break;

      default:
        break;
      }

      if (acquire)
      {
        printw ("Acquiring %s\n", mapObject[map[x][y]]);
        map[x][y] = Seed;
      }

      printw ("\n");


      switch (ObjAtCurrentPos)
      {
      case politician:
        /* locations[foundpolitician][0] = x;
           locations[foundpolitician][1] = y;
           foundpolitician++; */

        if (documents)
        {
          if (accuse ())
          {
            documents--;
            indictedCtr++;
          }
        }
        else if (rings)
        {
          if (accuse ());
          {
            rings--;
            indictedCtr++;
          }
        }
        else if (!documents && !rings)
          printw
            ("If you had some incriminating documents or magic rings,\nyou'd be able to indict him.\n");
        break;

      case Wall:
        wall ();
        if (t == 1 && rings)
        {
          printw ("You ran into a wall and ruined a Magic Ring.\n");
          rings--;
        }
        else if (!t && !rings)
        {
          printw ("You ran into wall. (-1 hp)\n");
          health--;
        }
        break;

      case Lake:
        lake ();
        if (t == 1 && documents)
        {
          printw
            ("You fell into the lake and lost an incriminating document.\n");
          documents--;
        }
        else if (t == 0)
        {
          printw ("You fell into the lake and caught a cold. (-1 hp)\n");
          health--;
        }
        else if (t == 1)
        {
          printw
            ("You take a swim, get cleaned up, and feel refreshed. (+2 hp)\n\n");
          health = health + 2;
        }
        break;

      case MagicWaterfall:
        printw
          ("You swim at the base of the Magic Waterfall and feel much better. (+40 hp)\n");
        health = health + 40;
        map[x][y] = Dried_up_Waterfall;
        break;

      case Clearing:
        creature = rand () % CREATURE_COUNT;
        if (seeds)
        {
          printw ("You plant a seed. You feel better. (+1 hp)\n");
          seeds--;
          t = rand () % 4;

          if (t >= 0 && t < 3)
          {
                                        /**
					 * map[x][y] will equal one of the items for the enum declaration
					 * item 5-7
					 */
            map[x][y] = t + an_incriminating_document;
          }
          else
            map[x][y] = Grapevine;
        }

        t = rand () % 4;
        if (t < 3 && !swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\n(-%u HP)\n\n", creat[creature].name,
                  creat[creature].strength);
          health = health - creat[creature].strength;
        }
        else if (t < 3 && swords)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your sword\n", creat[creature].name);
          printw
            ("protected you. That sword is now broken and you discard it.\n\n");
          swords--;
        }
        else if (t < 3 && rings)
        {
          printw
            ("You had no cover in the clearing and have been attacked by\n");
          printw ("\n%s.\n\nFortunately your Magic\n", creat[creature].name);
          printw
            ("Ring protected you. That ring is now broken and you discard it.\n\n");
          rings--;
        }
        break;

      case Tree:
        tree ();
        if (t == 1)
        {
          printw ("You rest under the tree and feel better (+1 hp)\n");
          health++;
        }
        else if (!t)
        {
          printw
            ("A squirrel runs out of the tree,\nbites your ankle,\nand quickly disappears. (-1 hp)\n");
          health--;
        }
        break;

      case Seed:
        printw ("Acquiring Seed.\n");
        seeds++;
        map[x][y] = Clearing;
        break;

      case Grapevine:
        randgrape = rand () % 4;
        if (randgrape != 2)
        {
          printw ("You eat a grape and feel better. (+1 hp)\n");
          health++;
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
    prompt (politicianCtr, indictedCtr);
    showMap (Visited);
    refresh ();
  }

  clear ();

  printw ("\nOut of %d politicians, you have retired %d of them.\n",
          politicianCtr, indictedCtr);
  printw ("Your health is %d\n\n", health);

  showitems ();

  printw ("\nEnter 'x' to exit\n");
  refresh ();
  while ((c = getch ()) != EOF && c != 'x' && c != 'X')
  {
  }
  endwin ();


  return 0;


}
