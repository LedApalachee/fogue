#ifndef items_h
#define items_h

#include <darray.h>


typedef struct ItemInfo
{
	double weight;
	double size;
	int condition; // if it's less than 0, the item is marked as broken, rotten, etc.
				   // and it's bad for the owner to use it

	int damage; // when wielded; if the number is negative, the item is not a weapon
	int defence; // when worn; if the number is negative, the item is not a wear
	int nutrition; // when eaten; if the number is negative, the item is not comestible
	int quench; // when drunk; if the number is negative, the item is not a liquid

	// if the item is inventory (bag, backpack, etc.)
	int volume;
	darray content; // struct Entity*

	darray effects; // struct Effect

	uint8_t flags;
} ItemInfo;


#endif