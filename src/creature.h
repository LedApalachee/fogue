#ifndef creatures_h
#define creatures_h

#include <darray.h>


typedef struct CreatureInfo
{
	char* personal_name;
	double size;

	int level;
	int hp, max_hp;
	int xp, max_xp;

	int strength;
	int constitution;
	int dexterity;
	int intelligence;
	int wisdom;
	int charisma;

	struct Entity* wielded_item;
	darray worn_items; // struct Entity*

	darray effects; // int

	uint8_t flags;
} CreatureInfo;


void creature_on_new_level(struct Entity* creature); // must be called when the creature gains new level


#endif