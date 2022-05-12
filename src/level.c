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
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
		if (level->items[i] == 0)
		{
			level->items[i] = item;
			level->cur_items++;
			if (i > level->i_endofarr_index)
				level->i_endofarr_index = i;
			break;
		}
	GET_TILE(level, item->pos_x, item->pos_y)->item_id = item->id;
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
			rearrange_array(level->creatures, &level->c_endofarr_index);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}


int level_del_item(Level* level, int i_id)
{
	for (int i = 0; i <= level->i_endofarr_index; ++i)
		if (level->items[i] != 0 && level->items[i]->id == i_id)
		{
			GET_TILE(level, level->items[i]->pos_x, level->items[i]->pos_y)->item_id = 0;
			level->items[i] = 0;
			rearrange_array(level->items, &level->i_endofarr_index);
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
			rearrange_array(level->features, &level->f_endofarr_index);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}




// as the test shows, it works fine
void rearrange_array(void** arr, int* end_i)
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
					end_i_m = i;
				}
			}
	*end_i = end_i_m;
}
