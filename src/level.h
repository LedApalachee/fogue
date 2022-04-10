#ifndef level_h
#define level_h


// features
#define CHAR_NONE ' '
#define CHAR_FLOOR '.'
#define CHAR_WALL '#'
#define CHAR_DOOR_CLOSED '+'
#define CHAR_DOOR_OPENED '\''
#define CHAR_CHEST '='


// items
#define CHAR_WEAPON ')'
#define CHAR_ARMOR ']'
#define CHAR_MISSILE ';'
#define CHAR_COMESTIBLE '%'
#define CHAR_POTION '!'
#define CHAR_GOLD '$'


typedef struct Tile
{
	char feature;
	int item_id;
	int creature_id;
} Tile;


#define LEVEL_MAX_CREATURES 128
#define LEVEL_MAX_ITEMS 256

#define LEVEL_endofentities 1


typedef struct Level
{
	char* name;
	int type;

	int sizeX, sizeY;
	Tile* map;

	struct Player* player;
	// if an element is equal to "LEVEL_endofentities", it is the end of the array (like '\0')
	struct Creature* creatures[LEVEL_MAX_CREATURES];
	struct Item* items items[LEVEL_MAX_ITEMS];
} Level;

#define GET_TILE(level_ptr, x, y) (&map[x + y * level_ptr->sizeX])

#define LEVEL_MAX_X 256
#define LEVEL_MAX_Y 256


#endif