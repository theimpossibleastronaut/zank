/**
 *       Zank.c

//      Copyright 2012, 2016 Andy Alt <andyqwerty@users.sourceforge.net>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses/ncurses.h>

#define DEBUG 0
/**
 *  Define the grid size
 */

#define X 7
#define Y 7

/* #define VER "2016.07.24-01alpha" */
#define VER "unstable"
#define AUTHOR "Andy Alt, and inspired by games such as Zork, Legend of the Red Dragon (L.O.R.D.), and Lunatix"

/* #define OFF_MAP printw("\nYou were attacked while trying to invade the neighboring kingdom (-2 hp)\n"); health = health - 2; */

bool accuse(int *actions, int climate);
void showitems(void);
/* void showpoliticians(int foundpolitician); */

void tree(void);
void wall(void);
void lake(void);


void showMap(bool Visited[X][Y]);
void prompt(short pCtr, short iCtr);
bool borderPatrol(void);

int x,y;
int map[X][Y];

int documents = 0;
int rings = 0;
int swords = 0;
int seeds = 0;



int health = 100;

enum {
	Tree,
	Lake,
	Clearing,
	politician,
	Wall,
	an_incriminating_document,
	Sword,
	Magic_Ring,
	indicted_politician,
	MagicWaterfall,
	Dried_up_Waterfall,
	Seed,
	Grapevine
	};

int main(int argc, char **argv)
{
	int climate;
	char *habitat[] = {
		"a Tree",
		"a Lake",
		"a Clearing",
		"a politician",
		"a Wall",
		"an incriminating document",
		"a Sword",
		"a Magic Ring",
		"a retired politician",
		"a Magic Waterfall",
		"a Dried up Waterfall",
		"a Seed",
		"a Grapevine"
	};

	const char *CREATURES[] = {
		"an evil gorilla",
		"a deranged vulture",
		"Angry Smurf(tm)",
		"a religious fanatic",
		"an imaginary enemy", /* 5 */
		"Emperor Killewe",
		"meddling kids in a van",
		"everyone you ever wronged",
		"your worst nightmare",
		"a copyrighted creature called \"Gollum\"", /* 10 */
		"a starving artist",
		"an innocent-looking rabbit",
		"your own insecurities",
		"your evil twin",
		"a telemarketer",   /* 15 */
		"a nasty band of evil cannibalistic cave dwellers",
		"a band of bloodthirsty reporters",
		"lobbyists",
		"the Supreme Court",
		"political repercussions", /* 20 */
		"a misguided priest",
		"an lawman who has to feed his family",
		"your mom",
		"bad gas",
		"your underpaid babysitter", /* 25 */
		"the ogre next door",
		"a lightning bolt sent by Zeus",
		"a runaway airplane propeller",
		"a crazed drug addict",
		"Oscar the Grouch",  /* 30 */
		"an unusually agressive gerbil",
		"hallucinations",
		"a guilty conscience",
		"a sense of strangeness",
		"a flying six-volt lantern battery", /* 35 */
		"tax collectors"
	};

	const int CREATURE_COUNT = 36;
	int creature;

	int actions[] = { 0, 0, 0, 69, 1, 10, 10, 10 };

	char *item;

	bool deed;

	bool flag = 0;

	srand( time( 0 ) );

/**
 * Generate coordinates for Magic Waterfall
 */
	int rx, ry;
	rx = rand() % X;
	ry = rand() % Y;

/**
 * Initialize map
 */
	unsigned short column,row;
	int politicianCtr = 0;

	for (column = 0; column < X; column++)
	{
		for (row = 0; row < Y; row++)
		{
			if (rx != column || ry != row)
			{
				climate = rand() % 8;

				if (climate == politician)
					politicianCtr++;

				map[column][row] = climate;
			}
			else map[column][row] = MagicWaterfall;
		}
	}


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

	short c;

	initscr();

	printw("\nZank version %s\n", VER);
	printw("By %s\n", AUTHOR);
	printw("Special thanks to mzdelong\n");
	refresh();

	prompt(politicianCtr, indictedCtr);
	refresh();

	bool Visited[X][Y];
	/**
	 * Init Array
	 */
	 for (column=0; column<X; column++)
		for (row=0; row<Y; row++)
			Visited[column][row]=0;

	while ( ( c = getch() ) != EOF && health > 0 && politicianCtr != indictedCtr && c != 'q')
	{
		int t = rand() % 2;
		flag = 0;
		clear();
		switch (c)
		{
			case 'e':
			if ( y < Y - 1)
			{
				y = y + East;
				printw("East\n");
			}
			else {
				flag = borderPatrol();
			}
			break;

			case 'w':
			if ( y > 0)
			{
				y = y + West;
				printw("West\n");
			}
			else {
				flag = borderPatrol();
			}
			break;

			case 's':
			if (x > 0)
			{
				x = x + South;
				printw("South\n");
			}
			else{
				flag = borderPatrol();
			}
			break;

			case 'n':
			if ( x < X - 1 )
			{
				x = x + North;
				printw("North\n");
			}
			else {
				flag = borderPatrol();
			}
			break;

			case 'i':
			showitems();
			flag = 1;
			break;

			case 'h':
			printw("HP: %d\n\n",health);
			flag = 1;
			break;

			case '\n':
			prompt(politicianCtr, indictedCtr);
			flag = 1;
			break;

			case 'm':
			showMap(Visited);
			flag = 1;
			break;

			default:
			printw("That is not a valid direction\n");
			refresh();
			flag = 1;
			break;
		}

		if (!flag)
		{
			Visited[x][y] = 1;

			climate = map[x][y];
			item = strdup(habitat[climate]);

			printw("\nYou see %s\n", item);

/**
 * This needs to be reworked
 * actions[5],[6],or[7] will == 10, that would be the 6,7,8th item in the enum list
 * 10 is just an arbitrary value defined in actions[] to determine whether or not
 * an items can be acquired
 */

			if (actions[climate] == 10)
			{
				printw("Acquiring %s\n", item);

				if (strcmp(item,"an incriminating document") == 0 )
					documents++;
				else if (strcmp(item,"a Magic Ring") == 0 )
					rings++;
				else if (strcmp(item,"a Sword") == 0 )
					swords++;
				map[x][y] = Seed;
			}

			printw("\n");


			switch (climate)
			{
				int randgrape = rand() % 4;

				case politician:
				/* locations[foundpolitician][0] = x;
				locations[foundpolitician][1] = y;
				foundpolitician++; */

				if (documents)
				{
					deed = accuse(actions, climate);
					if (deed)
					{
						documents--;
						indictedCtr++;
					}
				}
				else if (rings)
				{
					deed = accuse(actions, climate);
					if (deed)
					{
						rings--;
						indictedCtr++;
					}
				}
				else if (! documents && ! rings)
					printw("If you had some incriminating documents or magic rings,\nyou'd be able to indict him.\n");
				break;

				case Wall:
				wall();
				if (t == 1 && rings)
				{
					printw("You ran into a wall and ruined a Magic Ring.\n");
					rings--;
				}
				else if (! t && ! rings)
				{
					printw("You ran into wall. (-1 hp)\n");
					health--;
				}
				break;

				case Lake:
				lake();
				if (t == 1 && documents)
				{
					printw("You fell into the lake and lost an incriminating document.\n");
					documents--;
				}
				else if (t == 0)
				{
					printw("You fell into the lake and caught a cold. (-1 hp)\n");
					health--;
				}
				else if (t == 1)
				{
					printw("You take a swim, get cleaned up, and feel refreshed. (+2 hp)\n\n");
					health = health + 2;
				}
				break;

				case MagicWaterfall:
				printw("You swim at the base of the Magic Waterfall and feel much better. (+40 hp)\n");
				health = health + 40;
				map[x][y] = 10;
				break;

				case Clearing:
				creature = rand() % CREATURE_COUNT;
				if (seeds)
				{
					printw("You plant a seed. You feel better. (+1 hp)\n");
					seeds--;
					map[x][y] = Grapevine;
				}

				if ( t == 1 && ! swords)
				{
					printw("You had no cover in the clearing and have been attacked by\n");
					printw("%s. (-5 hp)\n\n", CREATURES[creature]);
					health = health - 5;
				}
				else if (t == 1 && swords)
				{
					printw("You had no cover in the clearing and have been attacked by\n");
					printw("%s. Fortunately your sword\n", CREATURES[creature]);
					printw("protected you. That sword is now broken and you discard it.\n\n");
					swords--;
				}
				else if (t == 1 && rings) {
					printw("You had no cover in the clearing and have been attacked by\n");
					printw("%s. Fortunately your Magic\n", CREATURES[creature]);
					printw("Ring protected you. That ring is now broken and you discard it.\n\n");
					rings--;
				}
				break;

				case Tree:
				tree();
				if (t == 1)
				{
					printw("You rest under the tree and feel better (+1 hp)\n");
					health++;
				}
				else if ( ! t )
				{
					printw("A squirrel runs out of the tree, bites your ankle,\nand quickly disappears. (-1 hp)\n");
					health--;
				}
				break;

				case Seed:
				printw("Acquiring Seed.\n");
				seeds++;
				map[x][y] = Clearing;
				break;

				case Grapevine:
				if (randgrape != 2)
					printw("You eat a grape and feel better. (+1 hp)\n");
				else
				{
					printw("The grapes have been poisoned and gave you a bad day. (-10 hp)\n");
					health -= 10;
				}
				break;

				default:
				break;
			}
		}
	prompt(politicianCtr, indictedCtr);
	refresh();
	}

	clear();

	printw("\nOut of %d politicians, you have retired %d of them.\n", politicianCtr, indictedCtr);
	printw("Your health is %d\n\n", health);

	showitems();

	printw("\nEnter 'x' to exit\n");
	refresh();
	while ( ( c = getch() ) != EOF && c != 'x' && c != 'X')
	{}
	endwin();


	return 0;


}


bool accuse(int *actions, int climate)
{
	if (map[x][y] != indicted_politician)
	{
		printw("You've just indicted the politician!\n");
		/* retiredPoliticians++;

		locOfRetiredPoliticians[retiredPoliticians - 1][0] = x;
		locOfRetiredPoliticians[retiredPoliticians - 1][1] = y; */

		int t = rand() % 2;

		if ( ! t )
		{
			printw("You feel better. (+5 hp)\n");
			health = health + 5;
		}
		else if (t == 1)
		{
			printw("You have been blackmailed by an ally of the politican! (-5 hp)\n");
			health = health - 5;
		}

		map[x][y] = 8;
		return 1;
	}
	else
	{
		printw("This politician has been indicted recently.\n");
		return 0;
	}

}

void showitems(void) {

	printw("Your inventory:\n");
	if (swords || documents || rings || seeds) {
		printw("Swords: %d\n",swords);
		printw("Incriminating Documents: %d\n",documents);
		printw("Magic Rings: %d\n",rings);
		printw("Seeds: %d\n", seeds);
	}

	else
		printw("You're not carrying anything");

	printw("\n");

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

void tree(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	printw("  oOOOOo\n");
	printw(" oOOOOOOo\n");
	printw("oOOOOOOOOo\n");
	printw(" oOOOOOOo\n");
	printw("  OOOOo\n");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	printw("    \e[31;40mII\e[0m\n");
	printw("    \e[31;40mII\e[0m\n");
	printw("    \e[31;40mII\e[0m\n");
	printw("    \e[31;40mII\e[0m\n");
	printw("    \e[31;40mII\e[0m\n");
	printw("   \e[31;40m/xx\\\e[0m\n");
	attroff(COLOR_PAIR(2));
}


void wall(void) {
	start_color();
	init_pair(1, COLOR_RED, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	printw("HEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\n");
	printw("EHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\n");
	attroff(COLOR_PAIR(1));
	printw("\n");
}

void lake(void) {
	printw("  \e[37;46m__________\e[0m\n");
	printw(" \e[37;46m/..........\\\e[0m\n");
	printw(" \e[37;46m\\...........\\____\e[0m\n");
	printw(" \e[37;46m/................\\\e[0m\n");
	printw("\e[37;46m/ .................\\\e[0m\n");
	printw("\e[37;46m\\__________________/\e[0m\n");
	printw("\n");
}

void showMap(bool Visited[X][Y])
{
	int column, row;

	for (column= X - 1; column >= 0; column--)
	{
		printw("\n");
		for (row=0; row<Y; row++)
		{
			/* printw("%d", map[i][j]); */
			/* printw("(%d),(%d)", i, j); */
			#if DEBUG==1
				printw("%d", Visited[column][row]);
			#endif
			if (column == x && row == y)
				printw("@");
			else if (Visited[column][row] == 1)
				{
					if (map[column][row] == politician)
						printw("p");
					else if (map[column][row] == Wall)
						printw("W");
					else if (map[column][row] == Lake)
						printw("L");
					else if (map[column][row] == Grapevine)
						printw("G");
					else
						printw("X");
				}
			else
				printw("*");
		}
	}

	printw("\n");
}

void prompt(short pCtr, short iCtr)
{
	printw("\n(%d,%d) (politicians left to retire: %d) (HP: %d) (i,m,q[uit]) (e,w,n,s)? ",
		y, x, pCtr - iCtr, health);
	refresh();
}

bool borderPatrol(void)
{
	printw("\nYou were attacked while trying to invade the neighboring kingdom (-2 hp)\n"); 
	health = health - 2;
	return 1;
}

