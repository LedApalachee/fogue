#ifndef data_h
#define data_h


typedef struct ReadCreatureSettings
{
	int level_type; // creature of which level to select
} ReadCreatureSettings;


typedef struct ReadItemSettings
{
	// info
} ReadItemSettings;


typedef struct ReadMapObjectSettings
{
	// info
} ReadMapObjectSettings;


struct Entity* read_creature(ReadCreatureSettings settings);
struct Entity* read_item(ReadItemSettings settings);
struct Entity* read_mapobject(ReadMapObjectSettings settings);


#endif