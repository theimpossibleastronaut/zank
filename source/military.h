/** \file military.h */

#ifndef __military_h
#define __military_h

#include "zank.h"

#define BARRACKS_COST 250
#define GET_UNITS_COST 100

#define INTEREST .1

#define PAWN_STRENGTH 20
#define PAWN_ARMOR 10
#define PAWNS_PER_TURN 4

#define KNIGHT_STRENGTH (PAWN_STRENGTH * 2.5)
#define KNIGHT_ARMOR (PAWN_ARMOR * 2.5)
#define KNIGHTS_PER_TURN (PAWNS_PER_TURN / 4)

/** The attributes of each combat unit. This structure is not used directly,
 * but as a member of each unit structure */
typedef struct st_attributes st_attributes;
struct st_attributes {

  /** Strength */
  const float strength;

  /** Armor */
  const float armor;

  /** Number of each unit from the \ref st_army struct that the player has */
  int count;
};

/** Information about the pawn */
typedef struct st_pawn st_pawn;
struct st_pawn {

  /** The information from \ref st_attributes */
  st_attributes attribute;
};

/** Information about the knight */
typedef struct st_knight st_knight;
struct st_knight {
  /** The information from \ref st_attributes */
  st_attributes attribute;
};

/** Encompasses all the the information about each combat unit. This struct
 * is not used directly, but is a member of \ref st_player_data */
struct st_army {
  st_pawn pawn;
  st_knight knight;
};

void construct_barracks (st_player_data *player);

void train_units (st_player_data *player);

#endif
