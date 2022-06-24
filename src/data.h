#ifndef data_h
#define data_h

#include <stdint.h>
#include <randnum.h>
#include "level.h"
#include "item.h"
#include "ui.h"


#define MAX_CREATURE_TYPES 100
#define MAX_ITEM_TYPES 800
#define MAX_CRAFTS 3200
#define MAX_LEVEL_TYPES 50




typedef struct EffectInit
{
	randuint16_t type;
	randint16_t time;
} EffectInit;




typedef struct LimbInit
{
	uint8_t type;
	randint16_t max_hp;
	randint16_t armor_type;
	randint16_t weapon_type;
	int16_t remains_type; // which item represents this limb (e.g. when it was cut off)
} LimbInit;

// relation types
#define RELATION_HOSTILE -1
#define RELATION_NEUTRAL 0
#define RELATION_FRIENDLY 1

typedef struct CreatureInit
{
	int8_t type;
	char name[51];
	char description[201];
	chtype ch;

	int8_t strength;
	int8_t dexterity;
	int8_t constitution;
	int8_t intelligence;
	int8_t wisdom;
	int8_t charisma;
	int8_t ap; // action points

	LimbInit body[MAX_LIMBS];

	randint16_t satiety;
	int16_t metabolism;

	randfloat lift_limit;
	randint16_t inventory_item_types[CREATURE_MAX_ITEMS];
	randuint16_t inventory_item_numbers[CREATURE_MAX_ITEMS];

	uint8_t sight_distance;

	int8_t relationships[MAX_CREATURE_TYPES]; // relation types

	int8_t item_pref_rates[MAX_ITEM_TYPES];

	int16_t corpse_type; // which item represents remains of this creature
} CreatureInit;




typedef struct WeaponInit
{
	randint16_t melee_damage;
	randint16_t ranged_damage;
	int8_t ranged_break_number; // how much is condition decreased when someone shot with this weapon
	EffectInit effect; // when struck someone or something
	randint32_t condition;
} WeaponInit;


typedef struct ArmorInit
{
	randint16_t defence;
	int8_t limb_type; // e.g. you can wear a helmet only on your head
	randuint16_t effect_type; // is active during the whole time of wearing
	randint32_t condition;
} ArmorInit;


typedef struct MissileInit
{
	int16_t weapon_type; // which ranged weapon can shoot with this missile
	randint16_t damage;
	EffectInit effect; // is activated on a targeted creature
} MissileInit;


typedef struct ComestibleInit
{
	randint32_t nutrition;
	randint32_t shelf_life; // how many turns are left before it becomes rotten
	EffectInit comested_effect; // is activated when comested
	EffectInit rotten_effect; // is activated when comested rotten
} ComestibleInit;


typedef struct NoteInit
{
	char text[201];
	int8_t type;
	randuint8_t numofreveal;
} NoteInit;


typedef struct ItemInit
{
	int16_t type;
	char name[51];
	char description[201];
	chtype ch;

	randfloat weight;

	uint8_t category;
	union
	{
		WeaponInit weapon;
		ArmorInit armor;
		MissileInit missile;
		ComestibleInit comestible;
		NoteInit note;
	} info;
	uint8_t flags;
} ItemInit;




typedef struct LevelInit
{
	char name[51];
	char description[201];
	int8_t type;
	char mapgen_script[501]; // a file path
	randint8_t next_level;
} LevelInit;




#define MAX_CRAFT_INPUTS 10

typedef struct Craft
{
	int16_t type;
	int16_t input_types[MAX_CRAFT_INPUTS]; // item types
	int input_numbers[MAX_CRAFT_INPUTS];

	int8_t feature_needed;
	int8_t str_needed;
	int8_t dex_needed;
	int8_t con_needed;
	int8_t int_needed;
	int8_t wis_needed;
	int8_t chr_needed;

	int16_t output_type; // item type
	int output_number;
} Craft;

#define CRAFT_NOFEATURE_NEEDED 0
#define CRAFT_WORKSHOP_NEEDED 1
#define CRAFT_FORGE_NEEDED 2
#define CRAFT_KITCHEN_NEEDED 3
#define CRAFT_ALCHEMERY_NEEDED 4




// an index for these arrays is a "type" variable
CreatureInit creature_table[MAX_CREATURE_TYPES];
ItemInit item_table[MAX_ITEM_TYPES];
LevelInit level_table[MAX_LEVEL_TYPES];
Craft crafts[MAX_CRAFTS];




Creature* get_creature(Level* level, int8_t type, int x, int y);
Item* get_item(Level* level, int16_t type, int x, int y);
Level* get_level(int8_t type);


int load_creature_data(char* data_file_path);
int load_item_data(char* data_file_path);
int load_level_data(char* data_file_path);
int load_craft_data(char* data_file_path);


int init_creature_table();
int init_item_table();
int init_level_table();
int init_crafts();



int scan_randint64_t(randint64_t* rn, char* str, char terminator);
int scan_randint32_t(randint32_t* rn, char* str, char terminator);
int scan_randint16_t(randint16_t* rn, char* str, char terminator);
int scan_randint8_t(randint8_t* rn, char* str, char terminator);
int scan_randuint64_t(randuint64_t* rn, char* str, char terminator);
int scan_randuint32_t(randuint32_t* rn, char* str, char terminator);
int scan_randuint16_t(randuint16_t* rn, char* str, char terminator);
int scan_randuint8_t(randuint8_t* rn, char* str, char terminator);
int scan_randdouble(randdouble* rn, char*str, char terminator);
int scan_randfloat(randfloat* rn, char* str, char terminator);


// these do leave only a useful piece of the given string, removing whitespaces and other unwanted characters from it
// both create dynamically allocated strings, so remeber to free() them
char* get_fieldname(char* str);
char* get_valuestring(char* str);


#endif
