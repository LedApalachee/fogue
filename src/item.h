#ifndef item_h
#define item_h

#include <stdint.h>
#include "effects.h"


#define ITEM_MAX_EFFECTS 16


typedef struct Item
{
	int id;
	int type;
	char* name;
	char ch;
	float weight; // kg
	Effect effects[ITEMS_MAX_EFFECTS];
	
	struct Weapon* weapon_info;
	struct Armor* armor_info;
	struct Missile* missile_info;
	struct Comestible* comestible_info;
} Item;


typedef struct Weapon
{
	int16_t melee_damage;
	int16_t ranged_damage;
	uint16_t missile_type; // which missile is availible for this ranged weapon
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
	uint8_t type;
	int damage;
	uint16_t effect_type; // is activated on a targetted creature
} Missile;


typedef struct Comestible
{
	int nutrition;
	int quench;
	uint16_t effect_type; // is activated when comested
} Comestible;


#endif