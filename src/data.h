#ifndef data_h
#define data_h

#include <stdint.h>
#include <randnum.h>
#include "level.h"
#include "item.h"


#define MAX_CREATURE_TYPES 100
#define MAX_ITEM_TYPES 800
#define MAX_LEVEL_TYPES 50




typedef struct EffectInit
{
	randuint16_t type;
	randint16_t time_left;
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

	randint16_t inventory_item_types[CREATURE_MAX_ITEMS];
	randuint16_t inventory_item_numbers[CREATURE_MAX_ITEMS];

	int8_t relationships[MAX_CREATURE_TYPES]; // relation types

	int16_t corpse_type; // which item represents remains of this creature
} CreatureInit;




typedef struct WeaponInit
{
	randint16_t melee_damage;
	randint16_t ranged_damage;
	EffectInit effect; // when struck someone or something
	randint32_t condition;
} WeaponInit;


typedef struct ArmorInit
{
	randint16_t defence;
	randuint8_t limb_type; // e.g. you can wear a helmet only on your head
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
	randint32_t quench;
	randint32_t shelf_life; // how many turns are left before it becomes rotten
	EffectInit comested_effect; // is activated when comested
	EffectInit rotten_effect; // is activated when comested rotten
} ComestibleInit;


typedef struct NoteInit
{
	char* text;
	randuint8_t type;
	randuint8_t numofreveal;
} NoteInit;


typedef struct ItemInit
{
	uint16_t type;
	char name[51];
	char description[101];
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
	char* name;
	uint8_t type;
	char* mapgen_script;
	randint8_t next_level;
} LevelInit;




// an index for these arrays is a "type" variable
CreatureInit creature_table[MAX_CREATURE_TYPES];
ItemInit item_table[MAX_ITEM_TYPES];
LevelInit level_table[MAX_LEVEL_TYPES];




Creature* get_creature(uint8_t type);
Item* get_item(uint16_t type);
Level* get_level(uint8_t type);


int load_creature_data(char* data_file_path);
int load_item_data(char* data_file_path);
int load_level_data(char* data_file_path);


int init_creature_table();
int init_item_table();
int init_level_table();



int scan_randint64_t(randint64_t* rn, char* str, char terminator);
int scan_randint32_t(randint32_t* rn, char* str, char terminator);
int scan_randint16_t(randint16_t* rn, char* str, char terminator);
int scan_randint8_t(randint8_t* rn, char* str, char terminator);
int scan_randuint64_t(randuint64_t* rn, char* str, char terminator);
int scan_randuint32_t(randuint32_t* rn, char* str, char terminator);
int scan_randuint16_t(randuint16_t* rn, char* str, char terminator);
int scan_randuint8_t(randint8_t* rn, char* str, char terminator);
int scan_randdouble(randdouble* rn, char*str, char terminator);
int scan_randfloat(randfloat* rn, char* str, char terminator);


// these do leave only a useful piece of the given string, removing whitespaces and other unwanted characters from it
// both create dynamically allocated strings, so remeber to free() them
char* get_fieldname(char* str);
char* get_valuestring(char* str);


#endif
