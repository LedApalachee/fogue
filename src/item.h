#ifndef items_h
#define items_h

#include <darray.h>


typedef struct ItemInfo
{
	double mass;
	double size;
	int condition; // if it's less than 0, the item is considered broken, rotten, ragged, etc.
	int min_condition; // if current condition is equal or less than this, the item is completely destroyed and must be deleted

	int sharpness; // cutting damage
	int hardness; // bashing damage

	int defence; // when worn; if the number is negative, the item is not a wear

	struct ItemComestibleInfo* comestible_info; // if it's null, the item is not comestible
	struct ItemStorageInfo* storage_info; // if it's null, the item can't serve as a storage
	struct ItemRangedInfo* ranged_info; // if it's null, the item is not a ranged weapon

	uint8_t flags;
} ItemInfo;




typedef enum ItemEffect
{
	item_effect_none,

	item_effect_max
} ItemEffect;




typedef struct ItemStorageInfo
{
	int free_volume;
	int max_volume;
	darray content; // struct Entity*
} ItemStorageInfo;




typedef struct ItemRangedInfo
{
	darray availible_ammo; // enum ItemGroup (int)
	int capacity;
	darray magazine; // struct Entity*
	double linear_momentum; // holy fu*ck, this game has physics!
	uint8_t flags;
} ItemRangedInfo;




typedef struct ItemComestibleInfo
{
	int nutrition;
	int quench;
	ItemEffect effect; // activates when it's eaten or drunk
} ItemComestibleInfo;




typedef struct ItemBehavior
{

} ItemBehavior;




struct Entity* new_item(uint8_t generation_flags); // adds new item into the level in a certain way


#endif