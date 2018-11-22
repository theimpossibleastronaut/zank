/** \file military.h */

#define PAWN_STRENGTH 20
#define PAWN_ARMOR 10

#define KNIGHT_STRENGTH (PAWN_STRENGTH * 2.5)
#define KNIGHT_ARMOR (PAWN_ARMOR * 2.5)

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

typedef struct st_army st_army;
struct st_army {
  st_pawn pawn;
  st_knight knight;
};
