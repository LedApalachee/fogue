#ifndef map_object_h
#define map_object_h

#include <darray.h>


typedef struct MapObjectInfo
{
	int condition; // how much is left to break or ruin this map object

	// which items (or not items) are included to this map object's construction
	darray components; // struct Entity*

	// there must be other info, but I currently haven't decided which;
	// it will be revealing throughout the development

	uint8_t flags;
} MapObjectInfo;


#define mapobject_is_movable 1




typedef struct MapObjectBehavior
{

} MapObjectBehavior;




typedef enum MapObjectEffect
{
	mapobject_effect_none,

	mapobject_effect_max
} MapObjectEffect;




struct Entity* new_mapobject(uint8_t generation_flags); // adds new mapobject into the level in a certain way


#endif