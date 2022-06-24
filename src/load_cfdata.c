#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "errors.h"


#define CUR_CF crafts[cur_type]


int load_creature_data(char* data_file_path)
{
	FILE* file = fopen(data_file_path, "r");
	if (file == 0) return FILE_NOT_FOUND;

	int c = 'f'; // current character that is retreived from the file
	char str[2048]; // variable for storing temporary strings read from the file
	int cur_type = 0;
	int cur_input = -1;
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
			CUR_CF.type = cur_type;
			cur_input = -1;
		}

		else if (strcmp(fieldname, "input_type") == 0)
		{
			++cur_input;
			if (cur_input < MAX_CRAFT_INPUTS)
				CUR_CF.input_types[cur_input] = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "input_number") == 0)
		{
			if (cur_input < MAX_CRAFT_INPUTS)
				CUR_CF.input_numbers[cur_input] = atoi(valuestring);
		}

		else if (strcmp(fieldname, "feat_needed") == 0)
		{
			CUR_CF.feature_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "str_needed") == 0)
		{
			CUR_CF.str_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "dex_needed") == 0)
		{
			CUR_CF.dex_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "con_needed") == 0)
		{
			CUR_CF.con_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "int_needed") == 0)
		{
			CUR_CF.int_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "wis_needed") == 0)
		{
			CUR_CF.wis_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "chr_needed") == 0)
		{
			CUR_CF.chr_needed = atoi(valuestring);
		}

		else if (strcmp(fieldname, "output_type") == 0)
		{
			CUR_CF.output_type = atoi(valuestring) - 1;
		}

		else if (strcmp(fieldname, "output_number") == 0)
		{
			CUR_CF.output_number = atoi(valuestring);
		}

		free(fieldname);
		free(valuestring);
	}

	fclose(file);
}
