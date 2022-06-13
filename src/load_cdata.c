#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "data.h"


int load_creature_data(char* data_file_path)
{
	FILE* file = fopen(data_file_path, "r");
	if (file == 0) return FILE_WASNT_FOUND;

	// setting all creature-inits to their default state
	for (int i = 0; i < MAX_CREATURE_TYPES)
	{
		creature_table[i].type = 0;
		creature_table[i].name = 0;
		creature_table[i].description = 0;
		creature_table[i].ch = 0;
		creature_table[i].strength = 0;
		creature_table[i].dexterity = 0;
		creature_table[i].constituiton = 0;
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
			creature_table[i].body[j].armor_type.start = 0;
			creature_table[i].body[j].armor_type.end = 0;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].body[j].armor_type.set[k].p = 0;
			creature_table[i].body[j].weapon_type.start = 0;
			creature_table[i].body[j].weapon_type.end = 0;
			for (int k = 0; k < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].body[j].weapon_type.set[k].p = 0;
			creature_table[i].body[j].remains_type = 0;
		}
		for (int j = 0; j < CREATURE_MAX_ITEMS; ++j)
		{
			creature_table[i].inventory_item_types[j].start = 0;
			creature_table[i].inventory_item_types[j].end = 0;
			for (int k = 0; l < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].inventory_item_types[j].set[k].p = 0;
			creature_table[i].inventory_item_numbers[j].start = 0;
			creature_table[i].inventory_item_numbers[j].end = 0;
			for (int k = 0; l < MAX_RANDNUM_MEMBERS; ++k)
				creature_table[i].inventory_item_numbers[j].set[k].p = 0;
		}
		for (int j = 0; j < MAX_CREATURE_TYPES; ++j)
			creature_table[i].relationships[j] = RELATION_NEUTRAL;
		creature_table[i].corpse_type = 0;
	}


	// some needed variables
	int c;
	int i1;
	char str[2000];
	int len;
	char ch;
	int fg_color;
	int bg_color;
	int is_bold;
	int cur_limbs;
	int cur_type;

	// scanning the data
	for ((c = getc(file)) != EOF)
	{
		switch (c)
		{
			// encountered a new definition
			case 'N':
				cur_limbs = 0;
				c = getc(file); // jumping over ':'

				// scanning the type
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				cur_type = atoi(str);
				creature_table[cur_type].type = cur_type;

				// scanning the name
				len = 0;
				for (int i = 0; c != '\n' && c != EOF; ++i, ++len)
					str[i] = c = getc(file);
				str[len-1] = '\0';
				creature_table[cur_type].name = (char*)malloc(sizeof(char)*len);
				for (int i = 0; i < len; ++i)
					creature_table[cur_type].name[i] = str[i];
				break;


			// encountered a description field
			case 'D':
				c = getc(file); // jumping over ':'

				// scanning the description
				len = 0;
				for (int i = 0; c != '~' && c != EOF; ++i, ++len)
					str[i] = c = getc();
				str[len-1] = '\0';
				creature_table[cur_type].description = (char*)malloc(sizeof(char)*len);
				for (int i = 0; i < len; ++i)
					creature_table[cur_type].description[i] = str[i];
				break;


			// encountered a character field
			case 'C':
				c = getc(file); // jumping over ':'
				ch = c = getc(file); // reading the character
				c = getc(file); // jumping over ':'

				// scanning fg color
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				fg_color = atoi(str);

				// scanning bg color
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				bg_color = atoi(str);

				// scanning "is bold" flag
				if ((c = getc(file)) == 'T') is_bold = 1;
				else is_bold = 0;

				c = getc(file); // jumping over '\n'

				// making the chtype
				creature_table[cur_type].ch = ch | UI_COLOR_PAIR(fg_color, bg_color) | (is_bold ? A_BOLD : 0);
				break;


			// encountered a stats field
			case 'S':
				c = getc(file); // jumping over ':'

				// scanning strength
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].strength = atoi(str);

				// scanning dexterity
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].dexterity = atoi(str);

				// scanning constitution
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].constituiton = atoi(str);

				// scanning intelligence
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].intelligence = atoi(str);

				// scanning wisdom
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].wisdom = atoi(str);

				// scanning charisma
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].charisma = atoi(str);

				// scanning action points
				for (int i = 0; c != '\n' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].ap = atoi(str);
				break;


			// encountered a limb field
			case 'B':
				c = getc(file); // jumping over ':'

				// scanning limb type
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].body[cur_limbs].type = atoi(str);

				// scanning limb hp
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				scan_randint16_t(&creature_table[cur_type].body[cur_limbs].max_hp, str, ':');

				// scanning limb weapon
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				scan_randint16_t(&creature_table[cur_type].body[cur_limbs].weapon_type, str, ':');

				// scanning limb armor
				for (int i = 0; c != ':' && c != EOF; ++i)
					str[i] = c = getc(file);
				scan_randint16_t(&creature_table[cur_type].body[cur_limbs].armor_type, str, ':');

				// scanning limb remains
				for (int i = 0; c != '\n' && c != EOF; ++i)
					str[i] = c = getc(file);
				creature_table[cur_type].body[cur_limbs].remains_type = atoi(str);
				break;

			// to finish
		}
	}

	fclose(file);
}


/*
	это пиздец...
*/
