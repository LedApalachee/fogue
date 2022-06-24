#ifndef creature_h
#define creature_h

#include <stdint.h>
#include <curses.h>
#include "effects.h"


typedef struct Limb
{
	uint8_t type;
	int16_t hp, max_hp;
	int16_t armor_id;
	int16_t weapon_id;
} Limb;

#define MAX_LIMBS 16

#define LIMB_NONE 0
#define LIMB_HEAD 1
#define LIMB_TORSO 2
#define LIMB_LEG 3
#define LIMB_ARM 4
#define LIMB_TAIL 5


#define CREATURE_MAX_EFFECTS 16
#define CREATURE_MAX_ITEMS 27
#define CREATURE_MAX_ENEMIES 20
#define CREATURE_MAX_FRIENDS 20


typedef struct Creature
{
	int id; // if id equals 0, this creature is player
	int8_t type;
	char name[51];
	chtype ch;

	int16_t pos_x, pos_y;

	int8_t max_strength;
	int8_t max_dexterity;
	int8_t max_constitution;
	int8_t max_intelligence;
	int8_t max_wisdom;
	int8_t max_charisma;

	int8_t cur_strength;
	int8_t cur_dexterity;
	int8_t cur_constitution;
	int8_t cur_intelligence;
	int8_t cur_wisdom;
	int8_t cur_charisma;

	int8_t max_ap;
	int8_t cur_ap; // action points; if it's negative, it's considered how much turns are needed for commiting one action

	Effect effects[CREATURE_MAX_EFFECTS];

	Limb body[MAX_LIMBS];
	int16_t hp, max_hp; // general hp is a sum of all the limbs' hp-s
						// when a limb loses some number of hp, the general hp is decreased by the same number
						// but losses of general hp don't affect on limbs' ones
						// if general hp is <= 0, the creature dies

	int16_t max_satiety;
	int16_t cur_satiety;
	int16_t metabolism; // shows in how many turns satiety decreases by 1
						// if it's < 0, then it shows how much satiety decreases per one turn

	float lifted_weight;
	float lift_limit;
	int16_t inventory[CREATURE_MAX_ITEMS]; // array of item id-s
										   // worn or wielded items aren't stored in inventory

	// arrays of creature ids
	int16_t cur_enemies[CREATURE_MAX_ENEMIES];
	int16_t cur_friends[CREATURE_MAX_FRIENDS];

	uint8_t sight_distance;

	uint8_t flags;
} Creature;


#define CREATURE_IS_HIDDEN 1




/*    player special fields    */
Creature* player_ptr; // must be allocated in the beginning of the game and freed in the end
int known_crafts_number;
int16_t* known_craft_types; // must be allocated in the beginning of the game and freed in the end




void player_discover_craft(int16_t craft_type);


#endif
