/*
 * Zank.h
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


#ifndef INC_ZANK_H
#define INC_ZANK_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <ncurses.h>

#define DEBUG curses
/**
 *  Define the grid size
 */

#define X 10
#define Y 10

/* #define VER "2016.08.02.01alpha" */
#define VER "testing"
#define AUTHOR "Andy Alt"

#define CREATURE_COUNT 25

int x, y;
int map[X][Y];

int documents;
int rings;
int swords;
int seeds;
int health;

struct creatures
{
  char *name;
  unsigned short strength;
};

/**
* NOTE: the order here must match with the objects listed in the
* mapObjects[] declaration in main.c
*/
enum
{
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

#endif
