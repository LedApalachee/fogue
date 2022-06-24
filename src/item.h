#ifndef item_h
#define item_h

#include <stdint.h>
#include <curses.h>
#include "effects.h"


typedef struct Weapon
{
	int16_t melee_damage;
	int16_t ranged_damage;
	int8_t ranged_break_number; // how much is condition decreased when someone shot with this weapon
	Effect effect; // when struck someone or something
	int max_condition;
	int cur_condition;
} Weapon;


typedef struct Armor
{
	int16_t defence;
	uint8_t limb_type; // e.g. you can wear a helmet only on your head
	uint16_t effect_type; // is active during the whole time of wearing
	int max_condition;
	int cur_condition;
} Armor;


typedef struct Missile
{
	int16_t weapon_type; // which ranged weapon can shoot with this missile
	uint16_t damage;
	Effect effect; // is activated on a targetted creature
} Missile;


typedef struct Comestible
{
	int nutrition;
	int shelf_life_max;
	int shelf_life_left; // how many turns are left before it becomes rotten
	Effect comested_effect; // is activated when comested
	Effect rotten_effect; // is activated when comested rotten
} Comestible;


#define NOTE_REVEAL_MAX 8

typedef struct Note
{
	char text[201];
	uint8_t type;
	uint8_t reveal_x[NOTE_REVEAL_MAX];
	uint8_t reveal_y[NOTE_REVEAL_MAX];
	uint8_t numofreveal;
	int16_t craft_type;
} Note;

#define NOTE_JUST_TEXT 0
#define NOTE_REVEAL_ITEM 1
#define NOTE_REVEAL_CREATURE 2
#define NOTE_REVEAL_FEATURE 3
#define NOTE_REVEAL_CRAFT 4


#define ITEM_MAX_EFFECTS 16

typedef struct Item
{
	int id;
	int16_t type;
	char name[51];
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


// common flags
#define ITEM_IS_UNSTACKABLE 1 // like swords in Minecraft
#define ITEM_IS_HIDDEN 2
#define ITEM_IS_IN_INVENTORY 4
#define ITEM_IS_IN_EQUIPMENT 8

// flags for weapons
#define WEAPON_IS_TWO_HANDED 16
#define RANGED_NEEDS_STRENGTH 32


// item categories
#define ITEM_NONE 0
#define ITEM_WEAPON 1
#define ITEM_ARMOR 2
#define ITEM_MISSILE 3
#define ITEM_COMESTIBLE 4
#define ITEM_NOTE 5
#define ITEM_MISC 6
#define ITEM_MONEY 7


#endif
