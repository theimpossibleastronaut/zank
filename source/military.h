/** \file military.h */

#ifndef __military_h
#define __military_h

#include "Zank.h"

#define BARRACKS_COST 250
#define GET_UNITS_COST 100

#define INTEREST .1

#define PAWN_STRENGTH 20
#define PAWN_ARMOR 10
#define PAWNS_PER_TURN 4

#define KNIGHT_STRENGTH (PAWN_STRENGTH * 2.5)
#define KNIGHT_ARMOR (PAWN_ARMOR * 2.5)
#define KNIGHTS_PER_TURN (PAWNS_PER_TURN / 4)

typedef struct st_attributes st_attributes;
struct st_attributes {
  const float strength;
  const float armor;
  int count;
};

typedef struct st_pawn st_pawn;
struct st_pawn {
  st_attributes attribute;
};

typedef struct st_knight st_knight;
struct st_knight {
  st_attributes attribute;
};

struct st_army {
  st_pawn pawn;
  st_knight knight;
};

void construct_barracks (st_player_data *player);

void train_units (st_player_data *player);

#endif
