#ifndef level_h
#define level_h

#include <stdint.h>
#include "creature.h"
#include "item.h"
#include "feature.h"


typedef struct Tile
{
	char feature;
	uint16_t creature_id; // if 0, there is no creature
	uint16_t item_id; // if 0, there is no item
	uint16_t feature_id; // if 0, there is no feature that needs own struct
	uint8_t flags;
} Tile;

#define TILE_IS_PASSABLE 1
#define TILE_IS_TRANSPARENT 2
#define TILE_CONTAINS_PLAYER 4
#define TILE_IS_DESTROYABLE 8


#define LEVEL_MAX_CREATURES 64
#define LEVEL_MAX_ITEMS 256
#define LEVEL_MAX_FEATURES 256


typedef struct Level
{
	char* name;
	int type;

	int sizeX, sizeY;
	Tile* map;

	struct Player* player;

	struct Creature* creatures[LEVEL_MAX_CREATURES];
	int cur_creatures;
	int c_endofarr_index;
	int max_c_id;

	struct Item* items[LEVEL_MAX_ITEMS];
	int cur_items;
	int i_endofarr_index;
	int max_i_id;

	struct Feature* features[LEVEL_MAX_FEATURES];
	int cur_features;
	int f_endofarr_index;
	int max_f_id;
} Level;

#define GET_TILE(level_ptr, x, y) (&level_ptr->map[x + y * level_ptr->sizeX])


#define OBJ_NOT_FOUND 2

Creature* find_creature(Level* level, int c_id);
Item* find_item(Level* level, int i_id);
Feature* find_feature(Level* level, int f_id);


#define LEVEL_MAX_X 256
#define LEVEL_MAX_Y 256


#endif