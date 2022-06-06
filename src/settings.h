#ifndef settings_h
#define settings_h

#include <curses.h>


#define DEFAULT_PLAYER_SIGHT_DISTANCE 10
#define MAX_ITEMS_ON_TILE 10


#define MAX_KEYS_IN_ONE 4 // maximum keys related to the same action

// priority 1
int KEY_MOVE_UP[MAX_KEYS_IN_ONE];
int KEY_MOVE_DOWN[MAX_KEYS_IN_ONE];
int KEY_MOVE_LEFT[MAX_KEYS_IN_ONE];
int KEY_MOVE_RIGHT[MAX_KEYS_IN_ONE];

// priority 2
int KEY_MOVE_UP_LEFT[MAX_KEYS_IN_ONE];
int KEY_MOVE_DOWN_LEFT[MAX_KEYS_IN_ONE];
int KEY_MOVE_DOWN_RIGHT[MAX_KEYS_IN_ONE];
int KEY_MOVE_UP_RIGHT[MAX_KEYS_IN_ONE];

// priority 3
int KEY_STAY[MAX_KEYS_IN_ONE];

// priority 4
int KEY_EXIT_GAME[MAX_KEYS_IN_ONE];

// priority 5
int KEY_WINRESIZE[MAX_KEYS_IN_ONE];


#endif
