#include "level.h"
#include "ui.h"


void handle_KEY_MOVE_UP()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_y > 0)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y-1);
	else if (cursor_y > 0)
		--cursor_y;
}


void handle_KEY_MOVE_DOWN()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_y < ui_cur_level->size_y-1)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y+1);
	else if (cursor_y < mapwin_sy-1)
		++cursor_y;
}


void handle_KEY_MOVE_LEFT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x > 0)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x-1, ui_cur_level->creatures[0]->pos_y);
	else if (cursor_x > 0)
		--cursor_x;
}


void handle_KEY_MOVE_RIGHT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x < ui_cur_level->size_x-1)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x+1, ui_cur_level->creatures[0]->pos_y);
	else if (cursor_x < mapwin_sx-1)
		++cursor_x;
}


void handle_KEY_MOVE_UP_LEFT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x > 0 && ui_cur_level->creatures[0]->pos_y > 0)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x-1, ui_cur_level->creatures[0]->pos_y-1);
	else if (cursor_x > 0 && cursor_y > 0)
	{
		--cursor_x;
		--cursor_y;
	}
}


void handle_KEY_MOVE_DOWN_LEFT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x > 0 && ui_cur_level->creatures[0]->pos_y < ui_cur_level->size_y-1)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x-1, ui_cur_level->creatures[0]->pos_y+1);
	else if (cursor_x > 0 && cursor_y < mapwin_sy-1)
	{
		--cursor_x;
		++cursor_y;
	}
}


void handle_KEY_MOVE_DOWN_RIGHT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x < ui_cur_level->size_x-1 && ui_cur_level->creatures[0]->pos_y < ui_cur_level->size_y-1)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x+1, ui_cur_level->creatures[0]->pos_y+1);
	else if (cursor_x < mapwin_sx-1 && cursor_y < mapwin_sy-1)
	{
		++cursor_x;
		++cursor_y;
	}
}


void handle_KEY_MOVE_UP_RIGHT()
{
	if (!cursor_active)
		if (ui_cur_level->creatures[0]->pos_x < ui_cur_level->size_x-1 && ui_cur_level->creatures[0]->pos_y > 0)
			level_move_creature(ui_cur_level, 0, ui_cur_level->creatures[0]->pos_x+1, ui_cur_level->creatures[0]->pos_y-1);
	else if (cursor_x < mapwin_sx-1 && cursor_y > 0)
	{
		++cursor_x;
		--cursor_y;
	}
}


/*  this function is useless, but for the a e s t h e t i c goals I wrote it whatever, though it's commented and contains nothing
void handle_KEY_STAY()
{

}
*/


/*
void handle_KEY_EXIT_GAME()
{
	quit = 1;
}
*/


/*
void handle_KEY_CHECK_WINRESIZE()
{

}
*/
