#include "level.h"


Creature* find_creature(Level* level, int c_id)
{
	for (int i = 0; i < LEVEL_MAX_CREATURES; ++i)
	{
		if (i >= level->c_endofarr_index) break;
		if (level->creatures[i]->id == c_id) return level->creatures[i];
	}
	return OBJ_NOT_FOUND;
}


Item* find_item(Level* level, int i_id)
{
	for (int i = 0; i < LEVEL_MAX_ITEMS; ++i)
	{
		if (i >= level->i_endofarr_index) break;
		if (level->items[i]->id == i_id) return level->items[i];
	}
	return OBJ_NOT_FOUND;
}


Feature* find_feature(Level* level, int f_id)
{
	for (int i = 0; i < LEVEL_MAX_FEATURES; ++i)
	{
		if (i >= level->f_endofarr_index) break;
		if (level->features[i]->id == f_id) return level->features[i];
	}
	return OBJ_NOT_FOUND;
}

// these functions above need test
