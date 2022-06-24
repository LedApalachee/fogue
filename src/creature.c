#include <stdlib.h>
#include "creature.h"
#include "level.h"


void player_discover_craft(int16_t craft_type)
{
	if (known_crafts_number < MAX_CRAFTS) ++known_crafts_number;
	known_craft_types = realloc(known_craft_types, known_crafts_number * sizeof(int16_t));
	known_craft_types[known_crafts_number-1] = craft_type;
}
