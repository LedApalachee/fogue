#include <stdlib.h>
#include "data.h"
#include "errors.h"


int init_creature_table()
{
	for (int i = 0; i < MAX_CREATURE_TYPES; ++i)
	{
		creature_table[i].type = -1;
		for (int j = 0; j < 51; ++j)
			creature_table[i].name[j] = '\0';
		for (int j = 0; j < 201; ++j)
			creature_table[i].description[j] = '\0';
		for (int j = 0; j < MAX_LIMBS; ++j)
			creature_table[i].body[j].type = 0;
		for (int j = 0; j < CREATURE_MAX_ITEMS; ++j)
		{
			creature_table[i].inventory_item_types[j].start = -1;
			creature_table[i].inventory_item_types[j].end = -1;
			creature_table[i].inventory_item_types[j].set[0].p = 0;
		}
		for (int j = 0; j < MAX_CREATURE_TYPES; ++j)
			creature_table[i].relationships[j] = RELATION_NEUTRAL;
		for (int j = 0; j < MAX_ITEM_TYPES; ++j)
			creature_table[i].item_pref_rates[j] = 50;
		creature_table[i].corpse_type = -1;
	}
	known_crafts_number = 0;
	known_craft_types = 0;
	return ALL_GOOD;
}


int init_item_table()
{
	for (int i = 0; i < MAX_ITEM_TYPES; ++i)
	{
		item_table[i].type = -1;
		for (int j = 0; j < 51; ++j)
			item_table[i].name[j] = '\0';
		for (int j = 0; j < 201; ++j)
			item_table[i].description[j] = '\0';
		item_table[i].category = ITEM_NONE;
		item_table[i].flags = 0;
	}
	return ALL_GOOD;
}


int init_crafts()
{
	for (int i = 0; i < MAX_CRAFTS; ++i)
	{
		crafts[i].type = -1;
		for (int j = 0; j < MAX_CRAFT_INPUTS; ++j)
		{
			crafts[i].input_types[j] = -1;
			crafts[i].input_numbers[j] = 0;
		}
		crafts[i].feature_needed = CRAFT_NOFEATURE_NEEDED;
		crafts[i].str_needed = 0;
		crafts[i].dex_needed = 0;
		crafts[i].con_needed = 0;
		crafts[i].int_needed = 0;
		crafts[i].wis_needed = 0;
		crafts[i].chr_needed = 0;
		crafts[i].output_type = -1;
		crafts[i].output_number = 0;
	}
	return ALL_GOOD;
}


// tested
char* get_fieldname(char* str)
{
	char* result;
	int len = 0;
	int i = 0;

	for ( ; ; ++i)
		if (str[i] >= 'A' && str[i] <= 'z') break;

	for (int j = i; str[j] != '=' && str[j] != ' ' && str[j] != '\n' && str[j] != '\t'; ++j)
		++len;

	result = (char*)malloc(len + 1);

	for (int j = 0; j < len; ++j)
		result[j] = str[i+j];
	result[len] = '\0';

	return result;
}


// tested
char* get_valuestring(char* str)
{
	char* result;
	int len = 0;
	int i = 0;
	int j = 0;

	for ( ; ; ++i)
	{
		if (str[i] == '\"' || str[i] == 'r' || str[i] == 's' || str[i] == '\'') break;
		else if (str[i] >= '0' && str[i] <= '9') break;
		else if (str[i] == '-') break;
	}

	switch (str[i])
	{
		case '\'':
			len = 2;
			result = (char*)malloc(len);
			result[0] = str[i+1];
			result[1] = '\0';
			break;

		case '\"':
			len = 1;
			for (j = i+1; str[j] != '\"'; ++j)
				++len;
			result = (char*)malloc(len + 1);
			for (j = 0; j < len-1; ++j)
				result[j] = str[i+1+j];
			result[len] = '\0';
			break;

		case 'r':
		case 's':
			j = i;
			len = 0;
			for ( ; str[j] != ';'; ++j)
				++len;
			result = (char*)malloc(len + 1);
			for (j = 0; j < len; ++j)
				result[j] = str[i+j];
			result[len] = '\0';
			break;

		case '-':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			j = i;
			len = 0;
			for ( ; str[j] != ';'; ++j)
				++len;
			result = (char*)malloc(len + 1);
			for (j = 0; j < len; ++j)
				result[j] = str[i+j];
			result[len] = '\0';
			break;
	}

	return result;
}


Creature* get_creature(Level* level, int8_t type, int x, int y)
{
	// checking, if everything fits in the level
	int ok = 1;
	// checking if creatures are not too much in the level
	if (level->cur_creatures >= LEVEL_MAX_CREATURES && x >= level->size_x && y >= level->size_y)
		ok = 0;

	if (GET_TILE(level, x, y)->creature_id != -1)
		ok = 0;

	// checking for creature's limbs' equipment
	for (int i = 0; i < MAX_LIMBS; ++i)
		if (creature_table[type].body[i].type != 0)
		{
			if (creature_table[type].body[i].armor_type.start != -1)
				if (level->cur_items >= LEVEL_MAX_ITEMS)
					ok = 0;

			if (creature_table[type].body[i].weapon_type.start != -1)
				if (level->cur_items >= LEVEL_MAX_ITEMS)
					ok = 0;
		}

	// checking for creature's inventory items
	for (int i = 0; i < CREATURE_MAX_ITEMS; ++i)
		if (creature_table[type].inventory_item_types[i] != -1)
			if (level->cur_items >= LEVEL_MAX_ITEMS)
				ok = 0;

	if (!ok) return 0;

	// creating new creature and its items
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	creature->pos_x = x;
	creature->pos_y = y;
}


Item* get_item(Level* level, int16_t type, int x, int y)
{

}


Level* get_level(int8_t type)
{

}
