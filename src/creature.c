#include <stdlib.h>
#include "creature.h"
#include "level.h"
#include "util.h"
#include "settings.h"


void player_discover_craft(int16_t craft_type)
{
	if (known_crafts_number < MAX_CRAFTS) ++known_crafts_number;
	known_craft_types = realloc(known_craft_types, known_crafts_number * sizeof(int16_t));
	known_craft_types[known_crafts_number-1] = craft_type;
}


int inventory_add_item(struct Level* level, struct Creature* creature, struct Item* item)
{
	if (creature->cur_items >= CREATURE_MAX_ITEMS) return CREATURE_INVENTORY_IS_FULL;
	if (level != 0)
	{
		Tile* cur_tile = GET_TILE(level, item->pos_x, item->pos_y);
		for (int i = 0; i < MAX_ITEMS_ON_TILE; ++i)
			if (cur_tile->item_ids[i] == item->id)
			{
				for (int j = i; j < MAX_ITEMS_ON_TILE-1; ++j)
					cur_tile->item_ids[j] = cur_tile->item_ids[j+1];
				--cur_tile->items_number;
			}
	}
	++creature->cur_items;
	creature->inventory[creature->cur_items-1] = item->id;
	item->flags |= ITEM_IS_IN_INVENTORY;
	item->pos_x = creature->pos_x;
	item->pos_y = creature->pos_y;
	return ALL_GOOD;
}


int inventory_del_item(struct Level* level, struct Creature* creature, struct Item* item)
{
	Tile* cur_tile;
	if (level != 0)
	{
		cur_tile = GET_TILE(level, item->pos_x, item->pos_y);
		if (cur_tile->items_number >= MAX_ITEMS_ON_TILE) return TOO_MANY_ITEMS_ON_TILE;
	}
	for (int i = 0; i < creature->cur_items; ++i)
		if (creature->inventory[i] == item->id)
		{
			for (int j = i; j < creature->cur_items-1; ++j)
				creature->inventory[j] = creature->inventory[j+1];
			--creature->cur_items;
			if (level != 0)
			{
				++cur_tile->items_number;
				cur_tile->item_ids[cur_tile->items_number-1] = item->id;
			}
			RESETF(item->flags, ITEM_IS_IN_INVENTORY);
			return ALL_GOOD;
		}
	return OBJ_NOT_FOUND;
}
