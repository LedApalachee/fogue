#ifndef print_h
#define print_h

#include "level.h"


int screen_size_x, screen_size_y;
char* string;

#define GET_SCREEN_TILE(x,y) (&string[x + y * screen_size_x])

void init_screen(Level* level);
void free_screen();
void reload_screen(Level* level);
void message(char* message); // like "you miss sewer rat. sewer rat hits you"


#endif