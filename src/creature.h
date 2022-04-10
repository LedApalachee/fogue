#ifndef creature_h
#define creature_h


typedef struct Limb
{
	int hp, max_hp;
	struct Item* armor;
	struct Item* wielded;
	uint8_t purpose;
} Limb;

#define MAX_LIMBS 16

#define LIMB_endoflimbs 1
#define LIMB_WALK 2
#define LIMB_HANDLE 4
#define LIMB_VITAL 8 // when it's destroyed, the creature dies


typedef struct Creature
{
	int id;
	char* name;
	char ch;

	int posX, posY;
	int hp, hp_max;

	int strength;
	int dexterity;
	int intelligence;

	Limb body[MAX_LIMBS];
} Creature;


typedef struct Player
{
	int posX, posY;
	int hp, hp_max;
	int xp, xp_max;
	int level;

	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;

	Limb body[MAX_LIMBS];
} Player;


#endif