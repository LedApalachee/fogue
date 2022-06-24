#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "data.h"
#include "ui.h"
#include "creature.h"


#define CUR_C creature_table[cur_type]


// tested
int load_creature_data(char* data_file_path)
{
	FILE* file = fopen(data_file_path, "r");
	if (file == 0) return FILE_NOT_FOUND;

	int c = 'f'; // current character that is retreived from the file
	char str[2048]; // variable for storing temporary strings read from the file
	int cur_type = 0;
	int ch;
	int fg_color, bg_color;
	int ch_bold;
	int limb_count = -1;
	int inventory_count = -1;
	int creature_type;
	int item_type;
	char* fieldname;
	char* valuestring;
	// there may be more variables if they're needed

	while (c != EOF)
	{
		// getting a field name
		for (int i = 0; c != '=' && c != EOF; ++i)
		{
			str[i] = c = getc(file);
			if (c == '#')
				while (c != '\n' && c != EOF)
					c = getc(file);
		}
		if (c == EOF) break;
		fieldname = get_fieldname(str);

		// getting a valuestring
		for (int i = 0; c != ';'; ++i)
			str[i] = c = getc(file);
		valuestring = get_valuestring(str);

		// processing the field
		if (strcmp(fieldname, "type") == 0)
		{
			cur_type = atoi(valuestring) - 1;
			CUR_C.type = cur_type;
			limb_count = -1;
			inventory_count = -1;
		}

		else if (strcmp(fieldname, "name") == 0)
		{
			strncpy(CUR_C.name, valuestring, 50);
			CUR_C.name[50] = '\0';
		}

		else if (strcmp(fieldname, "descr") == 0)
		{
			strncpy(CUR_C.description, valuestring, 200);
			CUR_C.description[200] = '\0';
		}

		else if (strcmp(fieldname, "ch") == 0)
		{
			ch = valuestring[0];
		}

		else if (strcmp(fieldname, "fg_color") == 0)
		{
			fg_color = atoi(valuestring);
		}

		else if (strcmp(fieldname, "bg_color") == 0)
		{
			bg_color = atoi(valuestring);
		}

		else if (strcmp(fieldname, "ch_bold") == 0)
		{
			ch_bold = atoi(valuestring);
			CUR_C.ch = ch | UI_COLOR_PAIR(fg_color, bg_color) | (ch_bold ? A_BOLD : 0);
		}

		else if (strcmp(fieldname, "str") == 0)
		{
			CUR_C.strength = atoi(valuestring);
		}

		else if (strcmp(fieldname, "dex") == 0)
		{
			CUR_C.dexterity = atoi(valuestring);
		}

		else if (strcmp(fieldname, "con") == 0)
		{
			CUR_C.constitution = atoi(valuestring);
		}

		else if (strcmp(fieldname, "int") == 0)
		{
			CUR_C.intelligence = atoi(valuestring);
		}

		else if (strcmp(fieldname, "wis") == 0)
		{
			CUR_C.wisdom = atoi(valuestring);
		}

		else if (strcmp(fieldname, "chr") == 0)
		{
			CUR_C.charisma = atoi(valuestring);
		}

		else if (strcmp(fieldname, "ap") == 0)
		{
			CUR_C.ap = atoi(valuestring);
		}

		else if (strcmp(fieldname, "limb_type") == 0)
		{
			++limb_count;
			if (limb_count < MAX_LIMBS)
				CUR_C.body[limb_count].type = atoi(valuestring);
		}

		else if (strcmp(fieldname, "limb_hp") == 0)
		{
			scan_randint16_t(&(CUR_C.body[limb_count].max_hp), valuestring, '\0');
		}

		else if (strcmp(fieldname, "limb_armor") == 0)
		{
			scan_randint16_t(&(CUR_C.body[limb_count].armor_type), valuestring, '\0');
			--CUR_C.body[limb_count].armor_type.start;
			--CUR_C.body[limb_count].armor_type.end;
			for (int i = 0; i < MAX_RANDNUM_MEMBERS && CUR_C.body[limb_count].armor_type.set[i].p != 0; ++i)
				--CUR_C.body[limb_count].armor_type.set[i].i;
		}

		else if (strcmp(fieldname, "limb_weapon") == 0)
		{
			scan_randint16_t(&(CUR_C.body[limb_count].weapon_type), valuestring, '\0');
			--CUR_C.body[limb_count].weapon_type.start;
			--CUR_C.body[limb_count].weapon_type.end;
			for (int i = 0; i < MAX_RANDNUM_MEMBERS && CUR_C.body[limb_count].weapon_type.set[i].p != 0; ++i)
				--CUR_C.body[limb_count].weapon_type.set[i].i;
		}

		else if (strcmp(fieldname, "limb_remains") == 0)
		{
			CUR_C.body[limb_count].remains_type = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "satiety") == 0)
		{
			scan_randint16_t(&CUR_C.satiety, valuestring, '\0');
		}

		else if (strcmp(fieldname, "metabolism") == 0)
		{
			CUR_C.metabolism = atoi(valuestring);
		}

		else if (strcmp(fieldname, "lift_limit") == 0)
		{
			scan_randfloat(&CUR_C.lift_limit, valuestring, '\0');
		}

		else if (strcmp(fieldname, "inv_item_type") == 0)
		{
			++inventory_count;
			if (inventory_count < CREATURE_MAX_ITEMS)
			{
				scan_randint16_t(&(CUR_C.inventory_item_types[inventory_count]), valuestring, '\0');
				--CUR_C.inventory_item_types[inventory_count].start;
				--CUR_C.inventory_item_types[inventory_count].end;
				for (int i = 0; i < MAX_RANDNUM_MEMBERS && CUR_C.inventory_item_types[inventory_count].set[i].p != 0; ++i)
					--CUR_C.inventory_item_types[inventory_count].set[i].i;
			}
		}

		else if (strcmp(fieldname, "inv_item_number") == 0)
		{
			scan_randuint16_t(&(CUR_C.inventory_item_numbers[inventory_count]), valuestring, '\0');
		}

		else if (strcmp(fieldname, "sight_dist") == 0)
		{
			CUR_C.sight_distance = atoi(valuestring);
		}

		else if (strcmp(fieldname, "creature_type") == 0)
		{
			creature_type = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "relation") == 0)
		{
			CUR_C.relationships[creature_type] = atoi(valuestring);
		}

		else if (strcmp(fieldname, "item_type") == 0)
		{
			item_type = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "pref_rate") == 0)
		{
			CUR_C.item_pref_rates[item_type] = atoi(valuestring);
		}

		else if (strcmp(fieldname, "corpse") == 0)
		{
			CUR_C.corpse_type = atoi(valuestring) - 1;
		}

		free(fieldname);
		free(valuestring);
	}

	fclose(file);
}
