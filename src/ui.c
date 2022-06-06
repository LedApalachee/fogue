#include <handleline.h>
#include "ui.h"
#include "settings.h"
#include "level.h"
#include "creature.h"
#include "item.h"
#include "errors.h"
#include "ascii.h"
#include "handle_key.h"


void init_pairs()
{
	for (int fg = 0; fg <= 17; ++fg)
		for (int bg = 0; bg <= 17; ++bg)
			init_pair(fg*16 + bg, fg, bg);
}


int ui_start()
{
	// "initscr" has already been called in "main"
	quit = 0;
	start_color();
	init_pairs();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
	mapwin_sx = MAPWIN_SX_RATIO * term_sx;
	mapwin_sy = MAPWIN_SY_RATIO * term_sy;
	infowin_sx = term_sx;
	infowin_sy = term_sy - mapwin_sy;
	statswin_sx = term_sx - mapwin_sx;
	statswin_sy = mapwin_sy;
	mapwin = newwin(mapwin_sy, mapwin_sx, 0, 0);
	infowin = newwin(infowin_sy, infowin_sx, mapwin_sy, 0);
	statswin = newwin(statswin_sy, statswin_sx, 0, mapwin_sx);
	for (int i = 0; i < MAX_MESSAGES; ++i)
		messages[i] = 0;
	wborder(infowin, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(statswin, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(mapwin);
	wrefresh(infowin);
	wrefresh(statswin);
	return ALL_GOOD;
}


void ui_finish()
{
	wclear(stdscr);
	endwin();
}


Level* cur_level;
Tile* cur_tile;
int i;
int draw_tile(int x, int y)
{
	if (i == 0)
	{
		++i;
		return ALL_GOOD;
	}
	if (x < 0 || y < 0 || x >= cur_level->size_x || y >= cur_level->size_y || i > cur_level->player->sight_distance) return BREAK_HANDLELINE;
	cur_tile = GET_TILE(cur_level, x, y);
	if (cur_tile->creature_id != -1)
	{
		Creature* cur_creature = cur_level->creatures[cur_tile->creature_id];
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_creature->ch);
	}
	else if (cur_tile->items_number > 0)
	{ 
		Item* cur_item = cur_level->items[cur_tile->item_ids[cur_tile->items_number-1]];
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_item->ch);
	}
	else
	{ 
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_tile->feature);
	}
	++i;
	if (!(cur_tile->flags & TILE_IS_TRANSPARENT)) return BREAK_HANDLELINE;
	return ALL_GOOD;
}


void ui_redraw_map(Level* level)
{
	wclear(mapwin);
	cur_level = level;
	mapwin_x = level->player->pos_x - mapwin_sx/2;
	mapwin_y = level->player->pos_y - mapwin_sy/2;
	for (int x = mapwin_x; x < mapwin_x + mapwin_sx; ++x)
	{
		i = 0;
		handleline(level->player->pos_x, level->player->pos_y, x, mapwin_y, &draw_tile);
		i = 0;
		handleline(level->player->pos_x, level->player->pos_y, x, mapwin_y + mapwin_sy-1, &draw_tile);
	}
	for (int y = mapwin_y; y < mapwin_y + mapwin_sy; ++y)
	{
		i = 0;
		handleline(level->player->pos_x, level->player->pos_y, mapwin_x, y, &draw_tile);
		i = 0;
		handleline(level->player->pos_x, level->player->pos_y, mapwin_x + mapwin_sx-1, y, &draw_tile);
	}
	mvwaddch(mapwin, level->player->pos_y - mapwin_y, level->player->pos_x - mapwin_x, CHAR_PLAYER);
	wrefresh(mapwin);
}


void ui_message(char* str)
{

}


void ui_popup(uint8_t type, void* content)
{

}


void ui_input(Level* level)
{
	int ch = getch();
	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP[i])
		{
			handle_KEY_MOVE_UP(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN[i])
		{
			handle_KEY_MOVE_DOWN(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_LEFT[i])
		{
			handle_KEY_MOVE_LEFT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_RIGHT[i])
		{
			handle_KEY_MOVE_RIGHT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_LEFT[i])
		{
			handle_KEY_MOVE_UP_LEFT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_RIGHT[i])
		{
			handle_KEY_MOVE_UP_RIGHT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN_LEFT[i])
		{
			handle_KEY_MOVE_DOWN_LEFT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN_RIGHT[i])
		{
			handle_KEY_MOVE_DOWN_RIGHT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_RIGHT[i])
		{
			handle_KEY_MOVE_UP_RIGHT(level);
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_STAY[i])
			return;

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_EXIT_GAME[i])
		{
			quit = 1;
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_WINRESIZE[i])
		{
			ui_winresize();
			mvwprintw(infowin, 2, 1, "window was resized: %dx%d", term_sx, term_sy);
			wrefresh(infowin);
			return;
		}
}


void ui_winresize()
{
	getmaxyx(stdscr, term_sy, term_sx);
	mapwin_sx = MAPWIN_SX_RATIO * term_sx;
	mapwin_sy = MAPWIN_SY_RATIO * term_sy;
	infowin_sx = term_sx;
	infowin_sy = term_sy - mapwin_sy;
	statswin_sx = term_sx - mapwin_sx;
	statswin_sy = mapwin_sy;
	mapwin = newwin(mapwin_sy, mapwin_sx, 0, 0);
	infowin = newwin(infowin_sy, infowin_sx, mapwin_sy, 0);
	statswin = newwin(statswin_sy, statswin_sx, 0, mapwin_sx);
	wborder(infowin, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(statswin, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(mapwin);
	wrefresh(infowin);
	wrefresh(statswin);
	refresh();
}
