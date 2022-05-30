#ifndef level_h
#define level_h

#include <stdint.h>
#include "creature.h"
#include "item.h"
#include "feature.h"
#include "settings.h"


typedef struct Tile
{
	char feature;
	uint16_t creature_id; // if 0, there is no creature
	uint16_t item_ids[MAX_ITEMS_ON_TILE];
	int8_t items_number; // how much items are in this tile
	uint16_t feature_id; // if 0, there is no special feature
	uint8_t flags;
} Tile;

#define TILE_IS_PASSABLE 1
#define TILE_IS_TRANSPARENT 2 // one's sight can pass through
#define TILE_CONTAINS_PLAYER 4
#define TILE_IS_DESTROYABLE 8
#define TILE_CAN_BURN 16
#define TILE_IS_BURNING 32


#define LEVEL_MAX_CREATURES 64
#define LEVEL_MAX_ITEMS 256
#define LEVEL_MAX_FEATURES 256


typedef struct Level
{
	char* name;
	uint8_t type;

	int size_x, size_y;
	Tile* map;

	Player* player;

	Creature* creatures[LEVEL_MAX_CREATURES];
	int cur_creatures;
	int c_endofarr_index;

	Item* items[LEVEL_MAX_ITEMS];
	int cur_items;
	int i_endofarr_index;

	Feature* features[LEVEL_MAX_FEATURES];
	int cur_features;
	int f_endofarr_index;
} Level;

#define GET_TILE(level_ptr, x, y) (&level_ptr->map[x + y * level_ptr->sizeX])




Creature* find_creature(Level* level, int c_id);
Item* find_item(Level* level, int i_id);
Feature* find_feature(Level* level, int f_id);


// adds object to appropriate array
// places it on the map
// performs some other actions if they're needed
int level_add_creature(Level* level, Creature* creature);
int level_add_item(Level* level, Item* item);
int level_add_feature(Level* level, Feature* feature, int pos_x, int pos_y);


// removes object from the map
// removes object from its array
int level_del_creature(Level* level, int c_id);
int level_del_item(Level* level, int i_id);
int level_del_feature(Level* level, int f_id);


void rearrange_ptr_array(void** arr, int* end_i) // compresses a pointer array by removing nulls from it
void rearrange_int_array(int* arr, int* end_i);


Level* generate_level(uint8_t type);
Level* create_blank_level(int sx, int sy);
int delete_level(Level* level, int free_level, int free_objects); // if "free_level" == true, "level" will be free()-ed
// if "free_objects" == true, all creatures, items and features will be free()-ed (except the player)


#define LEVEL_MAX_SX 256
#define LEVEL_MAX_SY 256


#endif
