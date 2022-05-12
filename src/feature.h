#ifndef feature_h
#define feature_h

#include <stdint.h>


#define CHEST_MAX_ITEMS 27

typedef struct Chest
{
	int condition;
	struct Item* items[CHEST_MAX_ITEMS];
	uint8_t flags;
} Chest;

#define CHEST_IS_LOCKED 1
#define CHEST_IS_HIDDEN 2


typedef struct Trap
{
	int type;
	uint8_t flags;
} Trap;

#define TRAP_IS_HIDDEN 1

typedef enum TrapType
{
	TRAP_NONE,
	TRAP_LANDMINE, // hurts limbs a lot
	TRAP_BEARTRAP, // hurts limbs and keeps creatures in this same tile
	TRAP_PIT, // keeps creatures in the same tile; after crawling out they are faint
	TRAP_SPIKE, // makes creatures bleed
	TRAP_FLASH, // makes creatures blind
	TRAP_FIRE, // puts creatures in fire
	TRAP_LMAO // does some shitty things
} TrapType;




typedef struct Door
{
	int condition;
	uint8_t flags;
} Door;

#define DOOR_IS_HIDDEN 1
#define DOOR_IS_LOCKED 2




typedef struct Feature
{
	uint16_t id;
	char ch;
	int pos_x, pos_y;
	union
	{
		Chest chest;
		Trap trap;
		Door door;
		int wall_condition;
	} info;
} Feature;


#endif
