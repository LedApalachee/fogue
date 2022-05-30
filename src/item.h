#ifndef item_h
#define item_h

#include <stdint.h>
#include <curses.h>
#include "effects.h"


typedef struct Weapon
{
	int16_t melee_damage;
	int16_t ranged_damage;
	Effect effect; // when struck someone or something
	int condition;
} Weapon;


typedef struct Armor
{
	int16_t defence;
	uint8_t limb_type; // e.g. you can wear a helmet only on your head
	uint16_t effect_type; // is active during the whole time of wearing
	int condition;
} Armor;


typedef struct Missile
{
	uint16_t weapon_type; // which ranged weapon can shoot with this missile
	uint16_t damage;
	Effect effect; // is activated on a targetted creature
} Missile;


typedef struct Comestible
{
	int nutrition;
	int quench;
	int shelf_life; // how many turns are left before it becomes rotten
	Effect comested_effect; // is activated when comested
	Effect rotten_effect; // is activated when comested rotten
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
	chtype ch;

	int16_t pos_x, pos_y;

	float weight; // weight of a unit of the item
	int number; // number of units of this item
	
	Effect effects[ITEM_MAX_EFFECTS];

	uint8_t category;
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

#define ITEM_IS_UNSTACKABLE 1 // like swords in Minecraft
#define ITEM_IS_HIDDEN 2
#define ITEM_IS_IN_INVENTORY 4

// flags for weapons
#define WEAPON_IS_TWO_HANDED 8

typedef enum ItemCategory
{
	ITEM_NONE,
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_MISSILE,
	ITEM_COMESTIBLE,
	ITEM_NOTE,
	ITEM_MISC,
	ITEM_MONEY
} ItemCategory;


#endif
