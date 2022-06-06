#include "level.h"
#include "ui.h"


void handle_KEY_MOVE_UP(Level* level)
{
	if (level->player->pos_y > 0)
		level_move_player(level, level->player->pos_x, level->player->pos_y-1);
}


void handle_KEY_MOVE_DOWN(Level* level)
{
	if (level->player->pos_y < level->size_y-1)
		level_move_player(level, level->player->pos_x, level->player->pos_y+1);
}


void handle_KEY_MOVE_LEFT(Level* level)
{
	if (level->player->pos_x > 0)
		level_move_player(level, level->player->pos_x-1, level->player->pos_y);
}


void handle_KEY_MOVE_RIGHT(Level* level)
{
	if (level->player->pos_x < level->size_x-1)
		level_move_player(level, level->player->pos_x+1, level->player->pos_y);
}


void handle_KEY_MOVE_UP_LEFT(Level* level)
{
	if (level->player->pos_x > 0 && level->player->pos_y > 0)
		level_move_player(level, level->player->pos_x-1, level->player->pos_y-1);
}


void handle_KEY_MOVE_DOWN_LEFT(Level* level)
{
	if (level->player->pos_x > 0 && level->player->pos_y < level->size_y-1)
		level_move_player(level, level->player->pos_x-1, level->player->pos_y+1);
}


void handle_KEY_MOVE_DOWN_RIGHT(Level* level)
{
	if (level->player->pos_x < level->size_x-1 && level->player->pos_y < level->size_y-1)
		level_move_player(level, level->player->pos_x+1, level->player->pos_y+1);
}


void handle_KEY_MOVE_UP_RIGHT(Level* level)
{
	if (level->player->pos_x < level->size_x-1 && level->player->pos_y > 0)
		level_move_player(level, level->player->pos_x+1, level->player->pos_y-1);
}


/*  this function is useless, but for the a e s t h e t i c goals I wrote it whatever, though it's commented and contains nothing
void handle_KEY_STAY(Level* level)
{

}
*/


/*
void handle_KEY_EXIT_GAME(Level* level)
{
	quit = 1;
}
*/


/*
void handle_KEY_CHECK_WINRESIZE()
{

}
*/
