/** \file zank.h
 * Globals for zank
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


#ifndef INC_ZANK_H
#define INC_ZANK_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <json.h>

/* On linux and mac, only <ncurses.h> is needed, but when using */
/* MinGW on Windows, the header can't be found unless this */
/* path is used */
#ifdef _WIN32
  #include <ncurses/ncurses.h>
#else
  #include <ncurses.h>
#endif

#define DEBUG curses

/**
 *  Define the map size
 */
#ifndef X
  #define X 10
#endif
#ifndef Y
  #define Y 10
#endif

/*
 * if parentheses aren't used here, rand doesn't produce
 * good results due to operator precedence
 */
#define MAP_SIZE (X * Y)

#define BUF_SIZE (512 + 1)
#define MAX_CELL_OBJECTS 4

#define PACKAGE "Zank"
#define VERSION "0.0.6-dev"
#define AUTHOR "Andy Alt"

/** Defines a single cell on a map. This structure is not used by itself, but
 * as a member of /ref st_map */
typedef struct st_cell st_cell;
struct st_cell {
  /** The 'x' coordinate of the cell */
  int pos_x;
  /** The 'y' coordinate of the cell */
  int pos_y;
  /** The \ref map_objects occupying the cell */
  int object[MAX_CELL_OBJECTS];

  /** Whether or not the cell has been explored */
  bool is_explored;
};

typedef struct st_map st_map;
struct st_map {
  st_cell cell[MAP_SIZE];
};

enum {
  WEST,
  EAST,
  NORTH,
  SOUTH,
};

typedef struct st_direction st_direction;
struct st_direction {
  char *str_which;
  int offset;
};

typedef struct st_assets st_assets;
typedef struct st_player_data st_player_data;
typedef struct st_army st_army;

/** \page code enumerated map objects
* \section map_objects Map Objects
*
* The order of each object must match with the objects listed in the
* mapObjects[] declaration in main.c
*/
enum
{
  TREE,
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
  Grapevine,
  DIAMOND_MINE,
  BARRACKS
};

#endif
