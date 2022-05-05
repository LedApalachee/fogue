#ifndef item_h
#define item_h

#include <stdint.h>
#include "effects.h"


typedef struct Weapon
{
	int16_t melee_damage;
	int16_t ranged_damage;
	int condition;
} Weapon;


typedef struct Armor
{
	int16_t armor_class;
	uint8_t limb_type; // e.g. you can wear a helmet only on your head
	uint16_t effect_type; // is active during the whole time of wearing
	int condition;
} Armor;


typedef struct Missile
{
	int weapon_type; // which ranged weapon can ballist this missile
	int damage;
	uint16_t effect_type; // is activated on a targetted creature
} Missile;


typedef struct Comestible
{
	int nutrition;
	int quench;
	uint16_t effect_type; // is activated when comested
} Comestible;


#define NOTE_REVEAL_MAX 8

typedef struct Note
{
	char* text;
	uint8_t type;
	uint8_t reveal_x[NOTE_REVEAL_MAX];
	uint8_t reveal_y[NOTE_REVEAL_MAX];
	uint8_t numofreveal;
} Note;

typedef enum NoteType
{
	NOTE_JUST_TEXT,
	NOTE_REVEAL_ITEM,
	NOTE_REVEAL_CREATURE,
	NOTE_REVEAL_FEATURE
} NoteType;


#define ITEM_MAX_EFFECTS 16

typedef struct Item
{
	int id;
	uint16_t type;
	char* name;

	int16_t posX, posY;

	float weight; // weight of a unit of the item
	int number;
	
	Effect effects[ITEMS_MAX_EFFECTS];

	uint8_t info_type;
	union
	{
		Weapon weapon;
		Armor armor;
		Missile missile;
		Comestible comestible;
		Note note;
	} info;

	uint8_t flags;
} Item;

#define ITEM_IS_UNPILABLE 1 // you can't store this item as multiple (like swords in Minecraft)
#define ITEM_IS_HIDDEN 2

typedef enum InfoType
{
	INFO_NONE,
	INFO_WEAPON,
	INFO_ARMOR,
	INFO_MISSILE,
	INFO_COMESTIBLE,
	INFO_NOTE,
	INFO_MISC,
	INFO_MONEY
} InfoType;


#endif