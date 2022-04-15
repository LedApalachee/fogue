#ifndef level_h
#define level_h

#include <stdint.h>


typedef struct Tile
{
	char feature;
	uint16_t item_id; // if it's 0, there is no item
	uint16_t creature_id;
	uint16_t feature_id;
	uint8_t flags;
} Tile;

#define TILE_IS_PASSABLE 1
#define TILE_IS_TRANSPARENT 2
#define TILE_CONTAINS_PLAYER 4
#define TILE_IS_DESTROYABLE 8
#define TILE_IS_HIDDEN_DOOR 16
#define TILE_IS_HIDDEN_TRAP 32


#define LEVEL_MAX_CREATURES 64
#define LEVEL_MAX_ITEMS 256
#define LEVEL_MAX_FEATURES 128

#define LEVEL_endofarr 1


typedef struct Level
{
	char* name;
	int type;

	int sizeX, sizeY;
	Tile* map;

	struct Player* player;
	// if an element is equal to LEVEL_endofarr, this is the end of the array (like '\0' in strings)
	struct Creature* creatures[LEVEL_MAX_CREATURES];
	struct Item* items[LEVEL_MAX_ITEMS];
	struct Feature* features[LEVEL_MAX_FEATURES];
} Level;

#define GET_TILE(level_ptr, x, y) (&map[x + y * level_ptr->sizeX])

#define LEVEL_MAX_X 256
#define LEVEL_MAX_Y 256


#endif