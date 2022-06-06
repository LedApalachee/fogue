#ifndef creature_h
#define creature_h

#include <stdint.h>
#include <curses.h>
#include "effects.h"


typedef struct Limb
{
	uint8_t type;
	int16_t hp, hp_max;
	int16_t armor_id;
	int16_t weapon_id;
} Limb;

#define MAX_LIMBS 16

typedef enum LimbType
{
	LIMB_NONE,
	LIMB_HEAD,
	LIMB_TORSO,
	LIMB_LEG,
	LIMB_ARM,
	LIMB_TAIL
} LimbType;


#define CREATURE_MAX_EFFECTS 16
#define CREATURE_MAX_ITEMS 27


typedef struct Creature
{
	int id;
	uint8_t type;
	char* name;
	chtype ch;

	int16_t pos_x, pos_y;

	int8_t strength;
	int8_t dexterity;
	int8_t constitution;
	int8_t intelligence;
	int8_t ap; // action points; if it's negative, it's considered how much turns are needed for commiting one action

	Effect effects[CREATURE_MAX_EFFECTS];

	Limb body[MAX_LIMBS];
	int16_t hp, hp_max; // general hp is a sum of all the limbs' hp-s
						// when a limb loses some number of hp, the general hp is decreased by the same number
						// but losses of general hp don't affect on limbs' ones
						// if general hp is <= 0, the creature dies

	float lifted_weight; // max weight is depends on the strength
	int16_t inventory[CREATURE_MAX_ITEMS]; // array of item id-s
										   // worn or wielded items aren't stored in inventory

	uint8_t sight_distance;

	uint8_t flags;
} Creature;

#define CREATURE_IS_HIDDEN 1


typedef struct Player
{
	char* name;
	int16_t pos_x, pos_y;
	int16_t xp, xp_max;
	int16_t level;

	int16_t strength;
	int16_t dexterity;
	int16_t constitution;
	int16_t intelligence;
	int16_t wisdom;
	int16_t charisma;
	uint8_t ap;

	int effects[CREATURE_MAX_EFFECTS];

	int16_t satiety; // if satiety <= 0 the general hp decreases by 1 every turn; also, physical stats are decreased by 25%
	int16_t max_satiety;

	Limb body[MAX_LIMBS];
	int16_t hp, hp_max;

	float lifted_weight; // max weight is depends on the strength
	struct Item* inventory[CREATURE_MAX_ITEMS];

	uint8_t sight_distance;
} Player;


#endif
