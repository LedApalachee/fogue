#ifndef handle_key_h
#define handle_key_h

#include "level.h"


void handle_KEY_MOVE_UP(Level* level);
void handle_KEY_MOVE_DOWN(Level* level);
void handle_KEY_MOVE_LEFT(Level* level);
void handle_KEY_MOVE_RIGHT(Level* level);
void handle_KEY_MOVE_UP_LEFT(Level* level);
void handle_KEY_MOVE_DOWN_LEFT(Level* level);
void handle_KEY_MOVE_DOWN_RIGHT(Level* level);
void handle_KEY_MOVE_UP_RIGHT(Level* level);
void handle_KEY_STAY(Level* level);
void handle_KEY_EXIT_GAME(Level* level);
void handle_KEY_CHECK_WINRESIZE();


#endif
