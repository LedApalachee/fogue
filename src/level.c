#include "level.h"
#include "ascii.h"
#include "errors.h"


Creature* find_creature(Level* level, int c_id)
{
	for (int i = 0; i <= level->c_endofarr_index; ++i)
		if (level->creatures[i] != 0 && level->creatures[i]->id == c_id) return level->creatures[i];
	return OBJ_NOT_FOUND;
}


Item* find_item(Level* level, int i_id)
{
	for (int i = 0; i <= level->i_endofarr_index; ++i)
		if (level->items[i] != 0 && level->items[i]->id == i_id) return level->items[i];
	return OBJ_NOT_FOUND;
}


Feature* find_feature(Level* level, int f_id)
{
	for (int i = 0; i <= LEVElevel->f_endofarr_indexL_MAX_FEATURES; ++i)
		if (level->features[i] != 0 && level->features[i]->id == f_id) return level->features[i];
	return OBJ_NOT_FOUND;
}

// these functions above (and beneath) need test


int level_add_creature(Level* level, Creature* creature)
{
	if (level->c_endofarr_index >= LEVEL_MAX_CREATURES-1) return OBJ_ARRAY_IS_FULL;
	for (int i = 0; i < LEVEL_MAX_CREATURES; ++i)
		if (level->creatures[i] == 0)
		{
			level->creatures[i] = creature;
			level->cur_creatures++;
			if (i > level->c_endofarr_index)
				level->c_endofarr_index = i;
			break;
		}
	GET_TILE(level, creature->pos_x, creature->pos_y)->creature_id = creature->id;
	return ALL_GOOD;
}


int level_add_item(Level* level, Item* item)
{
	if (level->i_endofarr_index >= LEVEL_MAX_ITEMS-1) return OBJ_ARRAY_IS_FULL;
	Tile* cur_tile;
	if ((cur_tile = GET_TILE(level, item->pos_x, item->pos_y))->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
		if (level->items[i] == 0)
		{
			level->items[i] = item;
			level->cur_items++;
			if (i > level->i_endofarr_index)
				level->i_endofarr_index = i;
			break;
		}
	cur_tile->item_ids[cur_tile->items_number] = item->id;
	cur_tile->items_number++;
	return ALL_GOOD;
}


int level_add_feature(Level* level, Feature* feature)
{
	if (level->f_endofarr_index >= LEVEL_MAX_FEATURES-1) return OBJ_ARRAY_IS_FULL;
	for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
		if (level->features[i] == 0)
		{
			level->features[i] = feature;
			level->cur_features++;
			if (i > level->f_endofarr_index)
				level->f_endofarr_index = i;
			break;
		}
	GET_TILE(level, feature->pos_x, feature->pos_y)->feature_id = feature->id;
	GET_TILE(level, feature->pos_x, feature->pos_y)->feature = feature->ch;
	return ALL_GOOD;
}




int level_del_creature(Level* level, int c_id)
{
	for (int i = 0; i <= level->c_endofarr_index; ++i)
		if (level->creatures[i] != 0 && level->creatures[i]->id == c_id)
		{
			GET_TILE(level, level->creatures[i]->pos_x, level->creatures[i]->pos_y)->creature_id = 0;
			level->creatures[i] = 0;
			rearrange_ptr_array(level->creatures, &level->c_endofarr_index);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}


int level_del_item(Level* level, int i_id)
{
	for (int i = 0; i <= level->i_endofarr_index; ++i)
		if (level->items[i] != 0 && level->items[i]->id == i_id)
		{
			Tile* cur_tile = GET_TILE(level, level->items[i]->pos_x, level->items[i]->pos_y);
			for (int j = 0; j < cur_tile->items_number; ++j)
				if (cur_tile->item_ids[j] == i_id)
				{
					cur_tile->item_ids[j] = 0;
					break;
				}
			int n = cur_tile->items_number-1;
			rearrange_int_array(cur_tile->item_ids, &n);
			cur_tile->items_number = n + 1;
			level->items[i] = 0;
			rearrange_ptr_array(level->items, &level->i_endofarr_index);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}


int level_del_feature(Level* level, int f_id)
{
	for (int i = 0; i <= level->f_endofarr_index; ++i)
		if (level->features[i] != 0 && level->features[i]->id == f_id)
		{
			GET_TILE(level, level->features[i]->pos_x, level->features[i]->pos_y)->feature_id = 0;
			GET_TILE(level, level->features[i]->pos_x, level->features[i]->pos_y)->feature = CHAR_FLOOR;
			level->features[i] = 0;
			rearrange_ptr_array(level->features, &level->f_endofarr_index);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}




// as the test showed, it works fine
void rearrange_ptr_array(void** arr, int* end_i)
{
	int end_i_m = *end_i;
	for (int i = 0; i <= end_i_m; ++i)
		if (arr[i] == 0)
			for (int j = end_i_m; j >= i; --j)
			{
				if (arr[j] != 0)
				{
					arr[i] = arr[j];
					arr[j] = 0;
					break;
				}
				if (j == i)
				{
					arr[i] = arr[end_i_m];
					arr[end_i_m] = 0;
					end_i_m = i-1;
				}
			}
	*end_i = end_i_m;
}


void rearrange_int_array(int* arr, int* end_i)
{
	int end_i_m = *end_i;
	for (int i = 0; i <= end_i_m; ++i)
		if (arr[i] == 0)
			for (int j = end_i_m; j >= i; --j)
			{
				if (arr[j] != 0)
				{
					arr[i] = arr[j];
					arr[j] = 0;
					break;
				}
				if (j == i)
				{
					arr[i] = arr[end_i_m];
					arr[end_i_m] = 0;
					end_i_m = i-1;
				}
			}
	*end_i = end_i_m;
}




Level* generate_level(uint8_t type)
{
	// this function will parse a mapgen script that is corresponding to the given type of level
}


Level* create_blank_level(int sx, int sy)
{
	Level* level = (Level*)malloc(sizeof(Level));
	level->name = "blank level";
	level->type = 1;
	level->size_x = sx;
	level->size_y = sy;

	// tiles
	level->map = (Tile*)malloc(sizeof(Tile) * sx * sy);
	for (int i = 0; i < sx*sy; ++i)
	{
		level->map[i].feature = CHAR_FLOOR;
		level->map[i].creature_id = 0;
		level->map[i].feature_id = 0;
		level->map[i].flags = TILE_IS_PASSABLE | TILE_IS_TRANSPARENT;
		for (int j = 0; j < MAX_ITEMS_ON_TILE; ++i)
			level->map[i].item_ids[j] = 0;
		level->map[i].items_number = 0;
	}

	level->player = 0;

	// creatures
	for (int i = 0; i < LEVEL_MAX_CREATURES; ++i)
		level->creatures[i] = 0;
	level->cur_creatures = 0;
	level->c_endofarr_index = 0;

	// items
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
		level->items[i] = 0;
	level->cur_items = 0;
	level->i_endofarr_index = 0;

	// features
	for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
		level->features[i] = 0;
	level->cur_features = 0;
	level->f_endofarr_index = 0;

	return level;
}


int delete_level(Level* level, int free_level, int free_objects)
{
	free(level->map);
	if (free_level) free(level);
	if (free_objects)
	{
		for (int i = 0; i < LEVEL_MAX_CREATURES; ++i)
			free(level->creatures[i]);

		for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
			free(level->items[i]);

		for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
			free(level->features[i]);
	}
	return ALL_GOOD;
}
