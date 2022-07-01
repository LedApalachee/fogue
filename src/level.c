#include <stdlib.h>
#include <string.h>
#include "level.h"
#include "ascii.h"
#include "errors.h"
#include "settings.h"
#include "util.h"
#include "creature.h"


int level_add_creature(Level* level, Creature* creature, int x, int y)
{
	if (level->cur_creatures >= LEVEL_MAX_CREATURES) return OBJ_ARRAY_IS_FULL;
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->creature_id != -1) return TILE_IS_OCCUPIED;
	for (int i = 1; i < LEVEL_MAX_CREATURES; ++i)
		if (level->creatures[i] == 0)
		{
			level->creatures[i] = creature;
			++level->cur_creatures;
			dest_tile->creature_id = i;
			creature->id = i;
			creature->pos_x = x;
			creature->pos_y = y;
			return ALL_GOOD;
		}
	return OBJ_ARRAY_IS_FULL;
}


int level_add_item(Level* level, Item* item, int x, int y, int inventory)
{
	if (level->cur_items >= LEVEL_MAX_ITEMS) return OBJ_ARRAY_IS_FULL;
	Tile* dest_tile = GET_TILE(level, x, y);
	if (inventory && dest_tile->creature_id == -1) return NOBODY_TO_POSSESS_ITEM;
	if (!inventory && dest_tile->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
		if (level->items[i] == 0)
		{
			if (inventory)
				if (inventory_add_item(0, level->creatures[dest_tile->creature_id], item) != ALL_GOOD)
					return NOBODY_TO_POSSESS_ITEM;
			else
			{
				++dest_tile->items_number;
				dest_tile->item_ids[dest_tile->items_number-1] = i;
			}
			level->items[i] = item;
			++level->cur_items;
			item->id = i;
			item->pos_x = x;
			item->pos_y = y;
			return ALL_GOOD;
		}
	return OBJ_ARRAY_IS_FULL;
}


int level_add_feature(Level* level, Feature* feature, int x, int y)
{
	if (level->cur_features >= LEVEL_MAX_FEATURES) return OBJ_ARRAY_IS_FULL;
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->feature_id != -1) return TILE_IS_OCCUPIED;
	for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
		if (level->features[i] == 0)
		{
			level->features[i] = feature;
			++level->cur_features;
			dest_tile->feature_id = i;
			dest_tile->flags = (feature->flags << (sizeof(dest_tile->flags)*8 - 4)) >> (sizeof(dest_tile->flags)*8 - 4);
			if (feature->flags & FEATURE_IS_HIDDEN)
			{
				dest_tile->ch = level->floor_ch;
				dest_tile->flags |= TILE_IS_TRANSPARENT;
			}
			else dest_tile->ch = feature->ch;
			feature->id = i;
			feature->pos_x = x;
			feature->pos_y = y;
			return ALL_GOOD;
		}
	return OBJ_ARRAY_IS_FULL;
}




int level_del_creature(Level* level, Creature* creature)
{
	if (level->creatures[creature->id] == 0) return OBJ_NOT_FOUND;
	GET_TILE(level, creature->pos_x, creature->pos_y)->creature_id = -1;
	level->creatures[creature->id] = 0;
	--level->cur_creatures;
	return ALL_GOOD;
}


int level_del_item(Level* level, Item* item)
{
	if (level->items[item->id] == 0) return OBJ_NOT_FOUND;
	Tile* cur_tile = GET_TILE(level, item->pos_x, item->pos_y);
	for (int i = 0; i < MAX_ITEMS_ON_TILE; ++i)
		if (cur_tile->item_ids[i] == item->id)
		{
			for (int j = i; j < MAX_ITEMS_ON_TILE-1; ++j)
				cur_tile->item_ids[j] = cur_tile->item_ids[j+1];
			--cur_tile->items_number;
		}
	level->items[item->id] = 0;
	--level->cur_items;
	return ALL_GOOD;
}


int level_del_feature(Level* level, Feature* feature)
{
	if (level->features[feature->id] == 0) return OBJ_NOT_FOUND;
	Tile* cur_tile = GET_TILE(level, feature->pos_x, feature->pos_y);
	cur_tile->feature_id = -1;
	cur_tile->ch = level->floor_ch;
	cur_tile->flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
	level->features[feature->id] = 0;
	--level->cur_features;
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
	level->type = -1;
	level->floor_ch = '.';
	level->water_ch = '~';
	level->size_x = sx;
	level->size_y = sy;

	// tiles
	level->map = (Tile*)malloc(sizeof(Tile) * sx * sy);
	for (int i = 0; i < sx*sy; ++i)
	{
		level->map[i].ch = level->floor_ch;
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
int level_move_creature(Level* level, Creature* creature, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->creature_id != -1) return TILE_IS_OCCUPIED;
	GET_TILE(level, creature->pos_x, creature->pos_y)->creature_id = -1;
	dest_tile->creature_id = creature->id;
	creature->pos_x = x;
	creature->pos_y = y;
	return ALL_GOOD;
}


// tested
int level_move_item(Level* level, Item* item, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	Tile* cur_tile = GET_TILE(level, item->pos_x, item->pos_y);
	if (dest_tile->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	for (int i = 0; i < MAX_ITEMS_ON_TILE; ++i)
		if (cur_tile->item_ids[i] == item->id)
		{
			for (int j = i; j < MAX_ITEMS_ON_TILE-1; ++j)
				cur_tile->item_ids[j] = cur_tile->item_ids[j+1];
			cur_tile->items_number--;
		}
	dest_tile->item_ids[dest_tile->items_number] = item->id;
	dest_tile->items_number++;
	item->pos_x = x;
	item->pos_y = y;
	return ALL_GOOD;
}


// tested
int level_move_feature(Level* level, Feature* feature, int x, int y)
{
	Tile* dest_tile = GET_TILE(level, x, y);
	if (dest_tile->feature_id != -1) return TILE_IS_OCCUPIED;
	Tile* cur_tile = GET_TILE(level, feature->pos_x, feature->pos_y);
	dest_tile->feature_id = feature->id;
	dest_tile->ch = cur_tile->ch;
	dest_tile->flags = cur_tile->flags;
	cur_tile->feature_id = -1;
	cur_tile->ch = level->floor_ch;
	cur_tile->flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
	feature->pos_x = x;
	feature->pos_y = y;
	return ALL_GOOD;
}
