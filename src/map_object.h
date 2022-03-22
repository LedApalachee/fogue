#ifndef map_object_h
#define map_object_h

#include <darray.h>


typedef struct MapObjectInfo
{
	int condotion; // how much is left to break or ruin this map object

	// which items (or not items) are included to this map object's construction
	darray components; // struct Entity*

	// there must be other info, but I currently haven't decided what
	// it will be revealing throughout the development

	uint8_t flags;
} MapObjectInfo;


typedef struct MapObjectBehavior
{

} MapObjectBehavior;


typedef enum MapObjectEffect
{
	map_object_effect_max,
} MapObjectEffect;


#endif