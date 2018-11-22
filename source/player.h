/** \file player.h
 */

#include "zank.h"
#include "military.h"

/** What the player has. This structure is not used by itself, but is
 * a member of /ref st_player_data */
struct st_assets {

  /** Number of documents */
  int documents;

  /** Number of magic rings */
  int rings;

  /** Number of swords */
  int swords;

  /** Number of seeds */
  int seeds;

  /** Number of diamond mines, each one produces x number of \ref diamonds per turn */
  int diamond_mine;

  /** Number of diamonds, which are produced from a \ref diamond_mine */
  float diamonds;

  /** Number of barracks the player has constructed */
  int barracks;
};

/** Holds the player data */
struct st_player_data {

  /** If connected as a client, the network address */
  char address[BUF_SIZE];

  /** Contains information from the \ref st_assets struct */
  st_assets inventory;

  /** Information from the \ref st_army struct */
  st_army army;

  int health;

  /** The cell the player is currently occupying */
  int cell;
};
