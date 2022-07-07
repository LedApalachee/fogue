#include <stdio.h>
#include <stdlib.h>
#include "ui/ui.h"
#include "level.h"
#include "errors.h"
#include "util.h"
#include "ascii.h"
#include "colors.h"

void init_settings();


int main(int argc, char** argv)
{
	initscr();
	getmaxyx(stdscr, term_sy, term_sx);
	if (term_sx < TERM_MIN_SX || term_sy < TERM_MIN_SY)
	{
		printw("The terminal window is too small.\nThe minimal resolution is %dx%d.\n", TERM_MIN_SX, TERM_MIN_SY);
		getch();
		ui_finish();
		return 0;
	}
	init_settings();
	ui_start();

	Level* level = create_blank_level(40, 40);

	Creature player;
	player.id = 0;
	player.ch = CHAR_PLAYER | UI_COLOR_PAIR(F_COLOR_RED, F_COLOR_BLACK) | A_BOLD;
	player.pos_x = level->size_x/2;
	player.pos_y = level->size_y/2;
	player.sight_distance = 10;

	level_add_creature(level, &player);

	for (int x = 0; x < level->size_x; ++x)
		for (int y = 0; y < level->size_y; ++y)
			GET_TILE(level, x, y)->ch = ',' | UI_COLOR_PAIR(F_COLOR_GREEN, F_COLOR_BLACK);

	// the loop:
	// 1) update screen
	// 2) handle input from user
	// 3) process entities' logic

	while (!quit)
	{
		ui_redraw_map(level);
		ui_input(level);
	}

	ui_finish();
	return 0;
}




void init_settings()
{
	KEY_MOVE_UP[0] = '8';
	KEY_MOVE_UP[1] = KEY_UP;

	KEY_MOVE_DOWN[0] = '2';
	KEY_MOVE_DOWN[1] = KEY_DOWN;

	KEY_MOVE_LEFT[0] = '4';
	KEY_MOVE_LEFT[1] = KEY_LEFT;

	KEY_MOVE_RIGHT[0] = '6';
	KEY_MOVE_RIGHT[1] = KEY_RIGHT;

	KEY_MOVE_UP_LEFT[0] = '7';

	KEY_MOVE_DOWN_LEFT[0] = '1';

	KEY_MOVE_DOWN_RIGHT[0] = '3';

	KEY_MOVE_UP_RIGHT[0] = '9';

	KEY_STAY[0] = '5';
	KEY_STAY[1] = ' ';

	KEY_EXIT_GAME[0] = 'q';

	KEY_WINRESIZE[0] = '`';
}
