#include "data.h"
#include <stdlib.h>


int init_creature_table()
{
	for (int i = 0; i < MAX_CREATURE_TYPES; ++i)
	{
		creature_table[i].type = -1;
		for (int j = 0; j < 51; ++j)
			creature_table[i].name[j] = '\0';
		for (int j = 0; j < 201; ++j)
			creature_table[i].description[j] = '\0';
		creature_table[i].ch = 0;
		creature_table[i].strength = 0;
		creature_table[i].dexterity = 0;
		creature_table[i].constitution = 0;
		creature_table[i].intelligence = 0;
		creature_table[i].wisdom = 0;
		creature_table[i].charisma = 0;
		creature_table[i].ap = 0;
		for (int j = 0; j < MAX_LIMBS; ++j)
		{
			creature_table[i].body[j].type = 0;
			creature_table[i].body[j].max_hp.start = 0;
			creature_table[i].body[j].max_hp.end = 0;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].body[j].max_hp.set[k].p = 0;
			creature_table[i].body[j].armor_type.start = -1;
			creature_table[i].body[j].armor_type.end = -1;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].body[j].armor_type.set[k].p = 0;
			creature_table[i].body[j].weapon_type.start = -1;
			creature_table[i].body[j].weapon_type.end = -1;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].body[j].weapon_type.set[k].p = 0;
			creature_table[i].body[j].remains_type = -1;
		}
		for (int j = 0; j < CREATURE_MAX_ITEMS; ++j)
		{
			creature_table[i].inventory_item_types[j].start = -1;
			creature_table[i].inventory_item_types[j].end = -1;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].inventory_item_types[j].set[k].p = 0;
			creature_table[i].inventory_item_numbers[j].start = 0;
			creature_table[i].inventory_item_numbers[j].end = 0;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].inventory_item_numbers[j].set[k].p = 0;
		}
		for (int j = 0; j < MAX_CREATURE_TYPES; ++j)
			creature_table[i].relationships[j] = RELATION_NEUTRAL;
		creature_table[i].corpse_type = -1;
	}
}




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
