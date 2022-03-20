#ifndef caver_h
#define caver_h

#include <stdint.h>
#include <darray.h>
#include "graphics.h"


// speaking generally - an entity is any material thing in the world
typedef struct Entity
{
	int id;
	char* name;
	char* description;
	struct Symbol symbol;

	int pos_x, pos_y;

	int type; // is it creature, item or map object (or maybe other thing)

	// each type of entities has its own set of information
	void* info;

	// every entity can be a member of various groups
	// (e.g. canines, traders, flying_beings, ranged_weapons, and more)
	darray groups; // int

	void (take_turn*)(struct Level*, struct Entity*);

	uint8_t flags;
} Entity;


#define entity_is_busy 1 // the entity might participate in a long interaction
#define entity_is_not_on_map 2 // e.g. when the entity is in a backpack or a chest


typedef enum EntityType
{
	entity_nothing,
	entity_map_object,
	entity_creature,
	entity_item,
	entity_projectile,

	entity_max
} EntityType;




typedef struct Interaction
{
	int type;
	Entity* active;
	Entity* passive;
	void* info;
	int duration;
} Interaction;


void start_interaction(struct Level* level, Interaction interaction);




typedef struct Effect
{
	int type;
	int current_duration;
	int max_duration;
} Effect;




typedef struct Tile
{
	// the first entity of the array is always map object (mostly floor or wall)
	darray entities; // struct Entity*
	uint8_t flags;
} Tile;


#define tile_is_passable 1
#define tile_contains_creatures 2




typedef struct Map
{
	int sizeX, sizeY;
	Tile* tiles;
	uint8_t flags;
} Map;

#define get_tile(map_ptr, x, y) (map_ptr->tiles[y * map_ptr->sizeX + x])




typedef struct Level
{
	Map map;

	// list of all entities on the level
	// struct Entity*
	darray creatures;
	darray items;
	darray map_objects;
	darray projectiles;

	uint64_t time; // counts turns

	uint8_t flags;
} Level;


void level_take_turn(Level* level);


#endif
