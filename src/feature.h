#ifndef feature_h
#define feature_h

#include <stdint.h>


#define CHEST_MAX_ITEMS 27

typedef struct Chest
{
	uint8_t flags;
	struct Item* items[CHEST_MAX_ITEMS];
} Chest;

#define CHEST_IS_LOCKED 1


typedef struct Feature
{
	uint16_t id;
	union
	{
		Chest chest;
		uint8_t trap_type;
	} info;
} Feature;


typedef enum TrapType
{
	TRAP_NONE,
	TRAP_LANDMINE,
	TRAP_BEARTRAP,
	TRAP_PIT
} TrapType;


#endif