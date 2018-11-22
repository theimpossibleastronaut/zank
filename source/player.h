/** \file player.h
 */

#include "Zank.h"
#include "military.h"

struct st_assets {
  int documents;
  int rings;
  int swords;
  int seeds;
  int diamond_mine;
  float diamonds;
  int barracks;
};

struct st_player_data {
  char address[BUF_SIZE];
  st_assets inventory;
  st_army army;
  int health;
  int cell;
};
