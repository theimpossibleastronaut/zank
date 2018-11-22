/** \file military.c
 */

#include "military.h"
#include "player.h"

st_pawn pawn = {PAWN_STRENGTH, PAWN_ARMOR};
st_knight knight = { KNIGHT_STRENGTH, KNIGHT_ARMOR };

extern st_map map;

/** Determine if a barracks is present in the current cell
 * @param [in] player
 * @return true or false
 */
static bool barracks_here (st_player_data *player)
{
  int i;
  for (i = 0; i < MAX_CELL_OBJECTS; i++)
    if (map.cell[player->cell].object[i] == BARRACKS)
      return true;

  return false;
}

void
construct_barracks (st_player_data *player)
{
  if (barracks_here (player))
  {
    printw ("You already have a Barracks here!\n");
    return;
  }

  if (player->inventory.diamonds < BARRACKS_COST)
  {
    printw ("You don't have enough money!\n");
    return;
  }

  int i;
  for (i = 0; i < MAX_CELL_OBJECTS; i++)
    if (map.cell[player->cell].object[i] == 0)
    {
      map.cell[player->cell].object[i] = BARRACKS;
      player->inventory.barracks++;
      player->inventory.diamonds -= BARRACKS_COST;
      printw ("Barracks constructed!\n");
      break;
    }
}

void
train_units (st_player_data *player)
{
  if (!barracks_here (player))
  {
    printw ("There is no barracks here!\n");
    return;
  }

  if (player->inventory.diamonds < GET_UNITS_COST)
  {
    printw ("You don't have enough money!\n");
    return;
  }

  if (player->inventory.diamonds >= GET_UNITS_COST)
  {
    printw ("%d pawns and %d knights have been trained\n", PAWNS_PER_TURN, KNIGHTS_PER_TURN);
    player->army.pawn.attribute.count += (PAWNS_PER_TURN * player->inventory.barracks);
    player->army.knight.attribute.count += (KNIGHTS_PER_TURN * player->inventory.barracks);
    player->inventory.diamonds -= GET_UNITS_COST;
  }
  return;
}
