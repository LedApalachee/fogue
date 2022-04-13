#ifndef level_h
#define level_h

#include <stdint.h>


typedef struct Tile
{
	char feature;
	int item_id; // if it's 0, there is no item
	int creature_id; // the same to creatures
	uint8_t flags;
} Tile;

#define TILE_IS_PASSABLE 1
#define TILE_IS_TRANSPARENT 2
#define TILE_CONTAINS_PLAYER 4
#define TILE_IS_DESTROYABLE 8


#define LEVEL_MAX_CREATURES 64
#define LEVEL_MAX_ITEMS 256

#define LEVEL_endofarr 1


typedef struct Level
{
	char* name;
	int type;

	int sizeX, sizeY;
	Tile* map;

	struct Player* player;
	// if an element is equal to LEVEL_endofarr, this is the end of the array (like '\0')
	struct Creature* creatures[LEVEL_MAX_CREATURES];
	struct Item* items items[LEVEL_MAX_ITEMS];
} Level;

#define GET_TILE(level_ptr, x, y) (&map[x + y * level_ptr->sizeX])

#define LEVEL_MAX_X 256
#define LEVEL_MAX_Y 256


#endif