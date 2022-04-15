#ifndef creature_h
#define creature_h

#include <stdint.h>
#include "effects.h"


typedef struct Limb
{
	int16_t hp, max_hp;
	uint8_t type;
	struct Item* armor;
	struct Item* weapon;
	uint8_t flags;
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

// flags in struct Limb
#define LIMB_IS_VITAL 1 // creature can't live without this limb
#define LIMB_CAN_WIELD 2
#define LIMB_CAN_WEAR 4


#define CREATURE_MAX_EFFECTS 16
#define CREATURE_MAX_ITEMS 26


typedef struct Creature
{
	int id;
	char* name;
	char ch;

	int16_t posX, posY;

	int16_t strength;
	int16_t dexterity;
	int16_t constitution;
	int16_t intelligence;

	Effect effects[CREATURE_MAX_EFFECTS];

	Limb body[MAX_LIMBS];

	float lifted_weight;
	struct Item* inventory[CREATURE_MAX_ITEMS]; // worn or wielded items aren't stored in inventory
} Creature;


typedef struct Player
{
	char* name;
	int16_t posX, posY;
	int16_t xp, xp_max;
	int16_t level;

	int16_t strength;
	int16_t dexterity;
	int16_t constitution;
	int16_t intelligence;
	int16_t wisdom;
	int16_t charisma;

	int effects[CREATURE_MAX_EFFECTS];

	Limb body[MAX_LIMBS];
	struct Item* inventory[CREATURE_MAX_ITEMS];
} Player;


#endif