/** \file military.c
 */

#include "military.h"
#include "player.h"

st_pawn pawn = {PAWN_STRENGTH, PAWN_ARMOR};
st_knight knight = { KNIGHT_STRENGTH, KNIGHT_ARMOR };

void
construct_barracks (st_player_data *player)
{
  extern st_map map;
  int i;
  bool barracks_here = 0;
  for (i = 0; i < MAX_CELL_OBJECTS; i++)
  if (map.cell[player->cell].object[i] == BARRACKS)
  {
    printw ("You already have a Barracks here!\n");
    barracks_here = 1;
    break;
  }

  if (!barracks_here)
  {
    for (i = 0; i < MAX_CELL_OBJECTS; i++)
      if (map.cell[player->cell].object[i] == 0)
      {
        map.cell[player->cell].object[i] = BARRACKS;
        player->inventory.barracks++;
        printw ("Barracks constructed!\n");
        break;
      }
  }
}
