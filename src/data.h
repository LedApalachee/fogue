#ifndef data_h
#define data_h

#include <stdint.h>
#include "level.h"
#include "item.h"
#include "randnum.h"


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
	randuint16_t max_hp;
	randuint16_t armor_type;
	randuint16_t weapon_type;
	uint16_t remains_item_type; // which item represents this limb (e.g. when it was cut off)
} LimbInit;

// relation types
#define RELATION_HOSTILE -1
#define RELATION_NEUTRAL 0
#define RELATION_FRIENDLY 1

typedef struct CreatureInit
{
	uint8_t type;
	char* name;
	char* description;
	chtype ch;

	int8_t strength;
	int8_t dexterity;
	int8_t constitution;
	int8_t intelligence;
	int8_t ap; // action points

	LimbInit body[MAX_LIMBS];

	randuint16_t inventory_item_types[CREATURE_MAX_ITEMS];
	randuint16_t inventory_item_numbers[CREATURE_MAX_ITEMS];

	int8_t relationships[MAX_CREATURE_TYPES]; // relation types

	uint16_t corpse_item_type; // which item represents remains of this creature
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
	uint16_t weapon_type; // which ranged weapon can shoot with this missile
	randuint16_t damage;
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
	char* name;
	char* description;
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
} LevelInit;




// an index for these arrays is "type" variable
CreatureInit creature_table[MAX_CREATURE_TYPES];
ItemInit item_table[MAX_ITEM_TYPES];
LevelInit level_table[MAX_LEVEL_TYPES];


Creature* get_creature(uint8_t type);
Item* get_item(uint16_t type);
Level* get_level(uint8_t type);




int load_creature_data(char* data_file_path);
int load_item_data(char* data_file_path);
int load_level_data(char* data_file_path);


#endif