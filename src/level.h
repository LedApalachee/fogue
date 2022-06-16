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
	int16_t creature_id; // if -1, there is no creature; the same is for ids from item_ids and feature_id
	int16_t item_ids[MAX_ITEMS_ON_TILE];
	int8_t items_number; // how much items are in this tile
	int16_t feature_id;
	uint8_t flags;
} Tile;

#define TILE_IS_PASSABLE 1
#define TILE_IS_TRANSPARENT 2 // one's sight can pass through this tile
#define TILE_IS_DESTROYABLE 4
#define TILE_CAN_BURN 8
#define TILE_IS_BURNING 16
#define TILE_CONTAINS_PLAYER 32


#define LEVEL_MAX_CREATURES 50
#define LEVEL_MAX_ITEMS 500
#define LEVEL_MAX_FEATURES 100

#define LEVEL_MAX_SX 256
#define LEVEL_MAX_SY 256


typedef struct Level
{
	char* name;
	uint8_t type;
	uint8_t next_level; // type of a next level

	int size_x, size_y;
	Tile* map;

	Player* player;

	Creature* creatures[LEVEL_MAX_CREATURES];
	int cur_creatures;

	Item* items[LEVEL_MAX_ITEMS];
	int cur_items;

	Feature* features[LEVEL_MAX_FEATURES];
	int cur_features;

	uint64_t time;
} Level;

#define GET_TILE(level_ptr, x, y) (&level_ptr->map[x + y * level_ptr->size_x])




// adds object to appropriate array
// places it on the map
// performs some other actions if they're needed
int level_add_creature(Level* level, Creature* creature);
int level_add_item(Level* level, Item* item);
int level_add_feature(Level* level, Feature* feature);


// removes object from the map
// removes object from its array
int level_del_creature(Level* level, int c_id);
int level_del_item(Level* level, int i_id);
int level_del_feature(Level* level, int f_id);


Level* generate_level(uint8_t type);
Level* create_blank_level(int sx, int sy);
int delete_level(Level* level, int free_level); // if "free_level" == true, "level" will be free()-ed


int level_move_player(Level* level, int x, int y);
int level_move_creature(Level* level, int c_id, int x, int y);
int level_move_item(Level* level, int i_id, int x, int y);
int level_move_feature(Level* level, int f_id, int x, int y);


#endif
