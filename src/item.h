#ifndef items_h
#define items_h

#include <darray.h>


typedef struct ItemInfo
{
	double weight;
	double size;
	int condition; // if it's less than 0, the item is considered broken, rotten, ragged, etc.
	int min_condition; // if current condition is equal or less than this, the item is completely destroyed and must be deleted

	int damage; // when wielded; if the number is negative, the item is not a weapon
	int defence; // when worn; if the number is negative, the item is not a wear
	int nutrition; // when eaten; if the number is negative, the item is not comestible
	int quench; // when drunk; if the number is negative, the item is not a liquid

	// if the item is inventory (bag, backpack, etc.)
	int volume; // if it's greater than 0, the item can be used as storage
	darray content; // struct Entity*

	darray effects; // struct Effect

	uint8_t flags;
} ItemInfo;


typedef struct ItemBehavior
{

} ItemBehavior;


typedef enum ItemEffect
{
	item_effect_max,
} ItemEffect;


#endif