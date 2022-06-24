#include <stdlib.h>
#include <string.h>
#include "level.h"
#include "ascii.h"
#include "errors.h"
#include "settings.h"
#include "util.h"


int level_add_creature(Level* level, Creature* creature)
{
	// step 1: check for exceptions
	if (level->cur_creatures >= LEVEL_MAX_CREATURES) return OBJ_ARRAY_IS_FULL;
	if (level->creatures[creature->id] != 0) return ID_ALREADY_EXISTS;
	Tile* dest_tile = GET_TILE(level, creature->pos_x, creature->pos_y);
	if (dest_tile->creature_id != -1) return TILE_IS_OCCUPIED;
	// step 2: add "creature" to the array
	for (int i = 1; i < LEVEL_MAX_CREATURES; ++ i)
		if (level->creatures[i] == 0)
		{
			creature->id = i;
			level->creatures[i] = creature;
			level->cur_creatures++;
			break;
		}
	// step 3: place "creature" on the map
	dest_tile->creature_id = creature->id;
	return ALL_GOOD;
}


// tested
int level_add_item(Level* level, Item* item)
{
	if (level->cur_items >= LEVEL_MAX_ITEMS) return OBJ_ARRAY_IS_FULL;
	if (level->items[item->id] != 0) return ID_ALREADY_EXISTS;
	Tile* cur_tile = GET_TILE(level, item->pos_x, item->pos_y);
	if (cur_tile->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	level->items[item->id] = item;
	level->cur_items++;
	cur_tile->item_ids[cur_tile->items_number] = item->id;
	cur_tile->items_number++;
	return ALL_GOOD;
}


// tested
int level_add_feature(Level* level, Feature* feature)
{
	if (level->cur_features >= LEVEL_MAX_FEATURES) return OBJ_ARRAY_IS_FULL;
	if (level->features[feature->id] != 0) return ID_ALREADY_EXISTS;
	Tile* dest_tile = GET_TILE(level, feature->pos_x, feature->pos_y);
	if (dest_tile->feature_id != -1) return TILE_IS_OCCUPIED;
	level->features[feature->id] = feature;
	level->cur_features++;
	dest_tile->feature_id = feature->id;
	dest_tile->flags = (feature->flags << 4) >> 4; // copying first four flags from "feature" to the destined tile
	if (feature->flags & FEATURE_IS_HIDDEN)
	{
		dest_tile->ch = CHAR_FLOOR;
		dest_tile->flags |= TILE_IS_TRANSPARENT;
	}
	else dest_tile->ch = feature->ch;
	return ALL_GOOD;
}




// tested
int level_del_creature(Level* level, int c_id, int to_free)
{
	if (level->creatures[c_id] == 0) return OBJ_NOT_FOUND;
	GET_TILE(level, level->creatures[c_id]->pos_x, level->creatures[c_id]->pos_y)->creature_id = -1;
	if (to_free) free(level->creatures[c_id]);
	level->creatures[c_id] = 0;
	level->cur_creatures--;
	return ALL_GOOD;
}


// i doubt this function very much
// P.S. i don't remember why
// tested
int level_del_item(Level* level, int i_id, int to_free)
{
	if (level->items[i_id] == 0) return OBJ_NOT_FOUND;
	Tile* cur_tile = GET_TILE(level, level->items[i_id]->pos_x, level->items[i_id]->pos_y);
	for (int i = 0; i < MAX_ITEMS_ON_TILE; ++i)
		if (cur_tile->item_ids[i] == i_id)
		{
			for (int j = i; j < MAX_ITEMS_ON_TILE-1; ++j)
				cur_tile->item_ids[j] = cur_tile->item_ids[j+1];
			cur_tile->items_number--;
		}
	if (to_free) free(level->items[i_id]);
	level->items[i_id] = 0;
	level->cur_items--;
	return ALL_GOOD;
}


// tested
int level_del_feature(Level* level, int f_id, int to_free)
{
	if (level->features[f_id] == 0) return OBJ_NOT_FOUND;
	Tile* cur_tile = GET_TILE(level, level->features[f_id]->pos_x, level->features[f_id]->pos_y);
	cur_tile->feature_id = -1;
	cur_tile->ch = level->floor_ch;
	cur_tile->flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
	if (to_free) free(level->features[f_id]);
	level->features[f_id] = 0;
	level->cur_features--;
	return ALL_GOOD;
}




Level* generate_level(int8_t type)
{
	// this function will parse a mapgen script corresponding to the given level type
}


// tested
Level* create_blank_level(int sx, int sy)
{
	Level* level = (Level*)malloc(sizeof(Level));
	strncpy(level->name, "blank_level", 50);
	level->type = 1;
	level->floor_ch = '.';
	level->size_x = sx;
	level->size_y = sy;

	// tiles
	level->map = (Tile*)malloc(sizeof(Tile) * sx * sy);
	for (int i = 0; i < sx*sy; ++i)
	{
		level->map[i].ch = CHAR_FLOOR;
		level->map[i].creature_id = -1;
		level->map[i].feature_id = -1;
		level->map[i].flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
		for (int j = 0; j < MAX_ITEMS_ON_TILE; ++j)
			level->map[i].item_ids[j] = -1;
		level->map[i].items_number = 0;
	}

	// creatures
	for (int i = 0; i < LEVEL_MAX_CREATURES; ++i)
		level->creatures[i] = 0;
	level->cur_creatures = 0;

	// items
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
		level->items[i] = 0;
	level->cur_items = 0;

	// features
	for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
		level->features[i] = 0;
	level->cur_features = 0;

	return level;
}


// tested
int delete_level(Level* level, int free_level)
{
	free(level->map);
	if (free_level) free(level);
	return ALL_GOOD;
}




// tested
int level_move_creature(Level* level, int c_id, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->creature_id != -1) return TILE_IS_OCCUPIED;
	GET_TILE(level, level->creatures[c_id]->pos_x, level->creatures[c_id]->pos_y)->creature_id = -1;
	dest_tile->creature_id = c_id;
	level->creatures[c_id]->pos_x = x;
	level->creatures[c_id]->pos_y = y;
	return ALL_GOOD;
}


// tested
int level_move_item(Level* level, int i_id, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	Tile* cur_tile = GET_TILE(level, level->items[i_id]->pos_x, level->items[i_id]->pos_y);
	if (dest_tile->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	for (int i = 0; i < MAX_ITEMS_ON_TILE; ++i)
		if (cur_tile->item_ids[i] == i_id)
		{
			for (int j = i; j < MAX_ITEMS_ON_TILE-1; ++j)
				cur_tile->item_ids[j] = cur_tile->item_ids[j+1];
			cur_tile->items_number--;
		}
	dest_tile->item_ids[dest_tile->items_number] = i_id;
	dest_tile->items_number++;
	level->items[i_id]->pos_x = x;
	level->items[i_id]->pos_y = y;
	return ALL_GOOD;
}


// tested
int level_move_feature(Level* level, int f_id, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->feature_id != -1) return TILE_IS_OCCUPIED;
	Tile* cur_tile = GET_TILE(level, level->features[f_id]->pos_x, level->features[f_id]->pos_y);
	dest_tile->feature_id = f_id;
	dest_tile->ch = cur_tile->ch;
	dest_tile->flags = cur_tile->flags;
	cur_tile->feature_id = -1;
	cur_tile->ch = CHAR_FLOOR;
	cur_tile->flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
	level->features[f_id]->pos_x = x;
	level->features[f_id]->pos_y = y;
	return ALL_GOOD;
}
