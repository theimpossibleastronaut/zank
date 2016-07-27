/**
 *       Zank.c

//      Copyright 2012, 2016 Andy Alt <andyqwerty@users.sourceforge.net>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
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


/* Define the grid size */
#define X 10
#define Y 10

/* #define VER "2016.07.24-01alpha" */
#define VER "unstable"
#define AUTHOR "Andy Alt, and inspired by games such as Zork, Legend of the Red Dragon (L.O.R.D.), and Lunatix"

const char BODY[] = "politician";
#define ACTION soil

#define CR printf("\n");
#define OFF_MAP printf("\nYou were attacked while trying to invade the neighboring kingdom (-2 hp)\n"); health = health - 2;
#define PROMPT CR printf("(%d,%d) (politicians left to retire: %d) (HP: %d) (i,m,q[uit]) (e,w,n,s)? ", y, x, politicians - indicted, health);


bool accuse(int *actions, int climate);
void showitems(void);
void showpoliticians(int foundpolitician);

void tree(void);
void wall(void);
void lake(void);


void showMap(void);


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
	Magic_Waterfall,
	Dried_up_Waterfall,
	Seed,
	Grapevine
	};

bool visited[X][Y];

/* Each time a politician is found, his location will be stored */
/* This variable name should be changed */
int locations[X * Y][2];

unsigned int locOfRetiredPoliticians[X][Y];
int retiredPoliticians = 0;

int main(int argc, char **argv)
{
	printf("\nZank version %s\n", VER);
	printf("By %s\n", AUTHOR);
	typedef unsigned char Loop;
	Loop i,j;

	int c;

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
		"those meddling kids from Scooby Doo",
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


	/* strcpy(habitat[4],BODY); */
	int actions[] = { 0, 0, 0, 69, 1, 10, 10, 10 };

	char *item;

	int t;
	bool deed;

	bool flag = 0;

	int rx, ry;
	rx = rand() % X;
	ry = rand() % Y;

	srand( time( 0 ) );

	short West = -1;
	short East = 1;
	short North = 1;
	short South = -1;

	int politicians = 0, indicted = 0;
	int foundpolitician = 0;


	for (i = 0; i < X; i++)
	{
		for (j = 0; j < Y; j++)
		{
			if (rx != i || ry != j)
			{
				climate = rand() % 8;

				if (climate == 3)
					politicians++;

				map[i][j] = climate;
			}
			else map[i][j] = 9;

		}
	}


	x = X / 2;
	y = Y / 2;

	PROMPT
	while ( ( c = getchar() ) != EOF && health > 0 && politicians != indicted && c != 'q')
	{
		t = rand() % 2;
		flag = 0;

		switch (c)
		{
			case 'e':
			if ( y < Y - 1)
			{
				y = y + East;
				visited[x][y] = 1;
			}
			else {
				OFF_MAP
				flag = 1;
			}
			break;

			case 'w':
			if ( y > 0)
			{
				y = y + West;
				visited[x][y] = 1;
			}
			else {
				OFF_MAP
				flag = 1;
			}
			break;

			case 's':
			if (x > 0)
			{
				x = x + South;
				visited[x][y] = 1;
			}
			else {
				OFF_MAP
				flag = 1;
			}
			break;

			case 'n':
			if ( x < X - 1 )
			{
				x = x + North;
				visited[x][y] = 1;
			}
			else {
				OFF_MAP
				flag = 1;
			}
			break;

			case 'i':
			showitems();
			flag = 1;
			break;

			case 'h':
			printf("HP: %d\n\n",health);
			flag = 1;
			break;

			case '\n':
			PROMPT
			flag = 1;
			break;

			case 'm':
			showMap();
			flag = 1;
			break;

			default:
			printf("That is not a valid direction\n");
			flag = 1;
			break;
		}

		if (! flag)
		{
			climate = map[x][y];
			item = strdup(habitat[climate]);
			CR

			printf("You see %s\n", item);

			if (actions[climate] == 10)
			{
				printf("Acquiring %s\n", item);

				if (strcmp(item,"an incriminating document") == 0 )
					documents++;
				else if (strcmp(item,"a Magic Ring") == 0 )
					rings++;
				else if (strcmp(item,"a Sword") == 0 )
					swords++;
				map[x][y] = Seed;
			}

			CR

			switch (climate)
			{
				case politician:
				locations[foundpolitician][0] = x;
				locations[foundpolitician][1] = y;
				foundpolitician++;

				if (documents)
				{
					deed = accuse(actions, climate);
					if (deed)
					{
						documents--;
						indicted++;
					}
				}
				else if (rings) {
					deed = accuse(actions, climate);
					if (deed) {
						rings--;
						indicted++;
					}
				}
				else if (! documents && ! rings)
					printf("If you had some incriminating documents or magic rings,\nyou'd be able to indict him.\n");
				else
					printf("After you attempt to seduce her, the politician will not have sex with you.\n");
				break;


				case Wall:
				wall();
				if (t == 1 && rings) {
					printf("You ran into a wall and ruined a Magic Ring.\n");
					rings--;
				}
				else if (! t && ! rings) {
					printf("You ran into wall. (-1 hp)\n");
					health--;
				}
				break;

				case Lake:
				lake();
				if (t == 1 && documents) {
					printf("You fell into the lake and lost an incriminating document.\n");
					documents--;
				}
				else if (t == 0) {
					printf("You fell into the lake and caught a cold. (-1 hp)\n");
					health--;
				}
				else if (t == 1) {
					printf("You take a swim, get cleaned up, and feel refreshed. (+2 hp)\n\n");
					health = health + 2;
				}
				break;

				case Magic_Waterfall:
				printf("You swim at the base of the Magic Waterfall and feel much better. (+40 hp)\n");
				health = health + 40;
				map[x][y] = 10;
				break;

				case Clearing:
				creature = rand() % CREATURE_COUNT;
				if (seeds) {
					printf("You plant a seed. You feel better. (+1 hp)\n");
					seeds--;
					map[x][y] = Grapevine;
				}
				if ( t == 1 && ! swords) {
					printf("You had no cover in the clearing and have been attacked by\n");
					printf("%s. (-5 hp)\n\n", CREATURES[creature]);
					health = health - 5;
				}
				else if (t == 1 && swords) {
					printf("You had no cover in the clearing and have been attacked by\n");
					printf("%s. Fortunately your sword\n", CREATURES[creature]);
					printf("protected you. That sword is now broken and you discard it.\n\n");
					swords--;
				}
				else if (t == 1 && rings) {
					printf("You had no cover in the clearing and have been attacked by\n");
					printf("%s. Fortunately your Magic\n", CREATURES[creature]);
					printf("Ring protected you. That ring is now broken and you discard it.\n\n");
					rings--;
				}
				break;

				case Tree:
				tree();
				if (t == 1) {
					printf("You rest under the tree and feel better (+1 hp)\n");
					health++;
				}
				else if ( ! t ) {
					printf("A squirrel runs out of the tree, bites your ankle,\nand quickly disappears. (-1 hp)\n");
					health--;
				}
				break;

				case Seed:
				printf("Acquiring Seed.\n");
				seeds++;
				map[x][y] = Clearing;
				break;

				case Grapevine: { int randgrape = rand() % 4;
				if (randgrape != 2) {
					printf("You eat a grape and feel better. (+1 hp)\n");
				}
				else {
					printf("The grapes have been poisoned and gave you a bad day. (-10 hp)\n");
					health -= 10;
				} }
				break;

				default:
				break;
			}
		}
	}



	CR
	printf("Out of %d politicians, you have retired %d of them.\n", politicians, indicted);
	printf("Your health is %d\n\n", health);

	showitems();

	printf("\nEnter 'x' to exit\n");
	while ( ( c = getchar() ) != EOF && c != 'x' && c != 'X')
	{}


	return 0;


}


bool accuse(int *actions, int climate)
{
	if (map[x][y] != 8)
	{
		printf("You've just indicted the politician!\n");
		retiredPoliticians++;

		locOfRetiredPoliticians[retiredPoliticians - 1][0] = x;
		locOfRetiredPoliticians[retiredPoliticians - 1][1] = y;

		int t = rand() % 2;

		if ( ! t )
		{
			printf("You feel better. (+5 hp)\n");
			health = health + 5;
		}
		else if (t == 1)
		{
			printf("You have been blackmailed by an ally of the politican! (-5 hp)\n");
			health = health - 5;
		}

		map[x][y] = 8;
		return 1;
	}
	else
	{
		printf("This politician has been indicted recently.\n");
		return 0;
	}

}

void showitems(void) {

	printf("Your inventory:\n");
	if (swords || documents || rings || seeds) {
		printf("Swords: %d\n",swords);
		printf("Incriminating Documents: %d\n",documents);
		printf("Magic Rings: %d\n",rings);
		printf("Seeds: %d\n", seeds);
	}

	else
		printf("You're not carrying anything");

	CR

}

void showpoliticians(int foundpolitician) {

	int i;
	printf("\nLocations of politicians:\n");
	printf("%3c %3c\n",'x', 'y');
	printf("-------------------\n");
	for (i = 0; i < foundpolitician; i++)
		printf("%3d %3d\n", locations[i][0], locations[i][1]);

	printf("--- Retired ---\n");
	for (i = 0; i < retiredPoliticians; i++)
		printf("%3d %3d\n", locOfRetiredPoliticians[i][0], locOfRetiredPoliticians[i][1]);
}

void tree(void) {
	printf("  \e[32;40moOOOOo\e[0m\n");
	printf(" \e[32;40moOOOOOOo\e[0m\n");
	printf("\e[32;40moOOOOOOOOo\e[0m\n");
	printf(" \e[32;40moOOOOOOo\e[0m\n");
	printf("  \e[32;40moOOOOo\e[0m\n");
	printf("    \e[31;40mII\e[0m\n");
	printf("    \e[31;40mII\e[0m\n");
	printf("    \e[31;40mII\e[0m\n");
	printf("    \e[31;40mII\e[0m\n");
	printf("    \e[31;40mII\e[0m\n");
	printf("   \e[31;40m/xx\\\e[0m\n");
}


void wall(void) {
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
	printf("\e[31;47mHEEHEEHEEHEEHEEHEEHEEHEEHEEHEEHE\e[0m\n");
	printf("\e[31;47mEHHEHHEHHEHHEHHEHHEHHEHHEHHEHHEH\e[0m\n");
}

void lake(void) {
	printf("  \e[37;46m__________\e[0m\n");
	printf(" /..........\\\n");
	printf(" \\...........\\____\n");
	printf(" /................\\\n");
	printf("/ .................\\\n");
	printf("\\__________________/\n");
}

void showMap(void)
{
	int i,j;

	for (i= X - 1; i >= 0; i--)
	{
		printf("\n");
		for (j=0; j<Y; j++)
		{
			/* printf("%d", map[i][j]); */
			/* printf("(%d),(%d)", i, j); */
			if (visited[i][j] == 1 && map[i][j] == politician)
				printf("p");
			else
			if (visited[i][j] == 1 && map[i][j] == Wall)
				printf("W");
			else
			if (visited[i][j] == 1 && map[i][j] == Lake)
				printf("L");
			else
			if (visited[i][j] == 1 && map[i][j] == Grapevine)
				printf("G");
			else
			if (i ==x && j ==y)
				printf("@");

			else
				printf("*");
		}
	}

	printf("\n");
}
