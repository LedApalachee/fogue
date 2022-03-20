#ifndef map_object_h
#define map_object_h


typedef struct MapObjectInfo
{
	int strength; // how much is left to break or ruin the map object

	// there must be other info, but I currently haven't decided what
	// it will reveal throughout the development

	uint8_t flags;
} MapObjectInfo;


#endif