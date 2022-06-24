#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "errors.h"


#define CUR_L level_table[cur_type]


int load_level_data(char* data_file_path)
{
	FILE* file = fopen(data_file_path, "r");
	if (file == 0) return FILE_NOT_FOUND;

	int c = 'f'; // current character that is retreived from the file
	char str[2048]; // variable for storing temporary strings read from the file
	int cur_type;
	char* fieldname;
	char* valuestring;

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
			CUR_L.type = cur_type;
		}

		else if (strcmp(fieldname, "name") == 0)
		{
			strncpy(CUR_L.name, valuestring, 50);
		}

		else if (strcmp(fieldname, "descr") == 0)
		{
			strncpy(CUR_L.description, valuestring, 200);
		}

		else if (strcmp(fieldname, "mapgen_script") == 0)
		{
			strncpy(CUR_L.mapgen_script, valuestring, 500);
		}

		else if (strcmp(fieldname, "next_level_type") == 0)
		{
			scan_randint8_t(&(CUR_L.next_level), valuestring, '\0');
		}

		free(fieldname);
		free(valuestring);
	}

	fclose(file);
}
