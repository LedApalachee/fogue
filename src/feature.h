#ifndef feature_h
#define feature_h

#include <stdint.h>


#define CHEST_MAX_ITEMS 27

typedef struct Chest
{
	int condition;
	int items[CHEST_MAX_ITEMS]; // these are ids of items
} Chest;


typedef enum TrapType
{
	TRAP_NONE,
	TRAP_LANDMINE, // hurts limbs a lot
	TRAP_BEARTRAP, // hurts limbs a little and keeps creatures in this tile for some time
	TRAP_PIT, // keeps creatures in this tile for some time; after crawling out they are faint
	TRAP_SPIKE, // makes creatures bleed
	TRAP_FLASH, // makes creatures blind
	TRAP_FIRE, // sets creatures in fire
	TRAP_LMAO // does some shitty things
} TrapType;


typedef struct Feature
{
	uint16_t id;
	char ch; // category of the feature is defined by its character
	int16_t pos_x, pos_y;
	union
	{
		Chest chest;
		int trap_type;
		int door_condition;
		int wall_condition;
	} info;
	uint8_t flags; // flag "define"s differ from one category to another but share the same "flags" variable
} Feature;


// this flag is common for all the categories
#define FEATURE_IS_PASSABLE 1
#define FEATURE_IS_TRANSPARENT 2 // one's sight can pass through this tile
#define FEATURE_IS_DESTROYABLE 4
#define FEATURE_CAN_BURN 8
#define FEATURE_IS_HIDDEN 16


// flag for a door
#define DOOR_IS_OPEN 32


// flag for a chest
#define CHEST_IS_LOCKED 32


#endif
