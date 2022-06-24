#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "data.h"
#include "item.h"

#define CUR_I item_table[cur_type]

int load_creature_data(char* data_file_path)
{
	FILE* file = fopen(data_file_path, "r");
	if (file == 0) return FILE_NOT_FOUND;

	int c = 'f'; // current character that is retreived from the file
	char str[2048]; // variable for storing temporary strings read from the file
	int cur_type = 0;
	char ch;
	int fg_color, bg_color;
	int ch_bold;
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
		}

		else if (strcmp(fieldname, "name") == 0)
		{
			strncpy(CUR_I.name, valuestring, 50);
		}

		else if (strcmp(fieldname, "descr") == 0)
		{
			strncpy(CUR_I.description, valuestring, 200);
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
			CUR_I.ch = ch | UI_COLOR_PAIR(fg_color, bg_color) | (ch_bold ? A_BOLD : 0);
		}

		else if (strcmp(fieldname, "weight") == 0)
		{
			scan_randfloat(&(CUR_I.weight), valuestring, '\0');
		}

		else if (strcmp(fieldname, "category") == 0)
		{
			CUR_I.category = atoi(valuestring);
		}

		else if (strcmp(fieldname, "malee_damage") == 0)
		{
			scan_randint16_t(&(CUR_I.info.weapon.melee_damage), valuestring, '\0');
		}

		else if (strcmp(fieldname, "ranged_damage") == 0)
		{
			scan_randint16_t(&(CUR_I.info.weapon.ranged_damage), valuestring, '\0');
		}

		else if (strcmp(fieldname, "ranged_break_num") == 0)
		{
			CUR_I.info.weapon.ranged_break_number = atoi(valuestring);
		}

		else if (strcmp(fieldname, "melee_effect_type") == 0)
		{
			scan_randuint16_t(&(CUR_I.info.weapon.effect.type), valuestring, '\0');
		}

		else if (strcmp(fieldname, "melee_effect_time") == 0)
		{
			scan_randint16_t(&(CUR_I.info.weapon.effect.time), valuestring, '\0');
		}

		else if (strcmp(fieldname, "weapon_condition") == 0)
		{
			scan_randint32_t(&(CUR_I.info.weapon.condition), valuestring, '\0');
		}

		else if (strcmp(fieldname, "is_twohanded") == 0)
		{
			CUR_I.flags |= WEAPON_IS_TWO_HANDED;
		}

		else if (strcmp(fieldname, "ranged_needs_strength") == 0)
		{
			CUR_I.flags |= RANGED_NEEDS_STRENGTH;
		}

		else if (strcmp(fieldname, "defence") == 0)
		{
			scan_randint16_t(&(CUR_I.info.armor.defence), valuestring, '\0');
		}

		else if (strcmp(fieldname, "armor_limb_type") == 0)
		{
			CUR_I.info.armor.limb_type = atoi(valuestring);
		}

		else if (strcmp(fieldname, "armor_effect") == 0)
		{
			scan_randuint16_t(&(CUR_I.info.armor.effect_type), valuestring, '\0');
		}

		else if (strcmp(fieldname, "armor_condition") == 0)
		{
			scan_randint32_t(&(CUR_I.info.armor.condition), valuestring, '\0');
		}

		else if (strcmp(fieldname, "missile_weapon_type") == 0)
		{
			CUR_I.info.missile.weapon_type = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "missile_damage") == 0)
		{
			scan_randint16_t(&(CUR_I.info.missile.damage), valuestring, '\0');
		}

		else if (strcmp(fieldname, "missile_effect_type") == 0)
		{
			scan_randuint16_t(&(CUR_I.info.missile.effect.type), valuestring, '\0');
		}

		else if (strcmp(fieldname, "missile_effect_time") == 0)
		{
			scan_randint16_t(&(CUR_I.info.missile.effect.time), valuestring, '\0');
		}

		else if (strcmp(fieldname, "nutrition") == 0)
		{
			scan_randint32_t(&(CUR_I.info.comestible.nutrition), valuestring, '\0');
		}

		else if (strcmp(fieldname, "shelf_life") == 0)
		{
			scan_randint32_t(&(CUR_I.info.comestible.shelf_life), valuestring, '\0');
		}

		else if (strcmp(fieldname, "comested_effect_type") == 0)
		{
			scan_randuint16_t(&(CUR_I.info.comestible.comested_effect.type), valuestring, '\0');
		}

		else if (strcmp(fieldname, "comested_effect_time") == 0)
		{
			scan_randint16_t(&(CUR_I.info.comestible.comested_effect.time), valuestring, '\0');
		}

		else if (strcmp(fieldname, "rotten_effect_type") == 0)
		{
			scan_randuint16_t(&(CUR_I.info.comestible.rotten_effect.type), valuestring, '\0');
		}

		else if (strcmp(fieldname, "rotten_effect_time") == 0)
		{
			scan_randint16_t(&(CUR_I.info.comestible.rotten_effect.time), valuestring, '\0');
		}

		else if (strcmp(fieldname, "text") == 0)
		{
			strncpy(CUR_I.info.note.text, valuestring, 200);
		}

		else if (strcmp(fieldname, "note_type") == 0)
		{
			CUR_I.info.note.type = atoi(valuestring);
		}

		else if (strcmp(fieldname, "numofreveal") == 0)
		{
			scan_randuint8_t(&(CUR_I.info.note.numofreveal), valuestring, '\0');
		}

		else if (strcmp(fieldname, "is_unstackable") == 0)
		{
			CUR_I.flags |= ITEM_IS_UNSTACKABLE;
		}

		free(fieldname);
		free(valuestring);
	}

	fclose(file);
}
