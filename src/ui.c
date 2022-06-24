#include <handleline.h>
#include "ui.h"
#include "settings.h"
#include "level.h"
#include "creature.h"
#include "item.h"
#include "errors.h"
#include "ascii.h"
#include "handle_key.h"


void ui_start()
{
	// "initscr" has already been called in "main"
	quit = 0;
	start_color();
	for (int fg = 0; fg <= 15; ++fg)
		for (int bg = 0; bg <= 15; ++bg)
			init_pair(fg*16 + bg, fg, bg);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();

	mapwin_sx = MAPWIN_SX_RATIO * term_sx - 2;
	mapwin_sy = MAPWIN_SY_RATIO * term_sy - 2;
	infowin_sx = term_sx - 2;
	infowin_sy = term_sy - mapwin_sy - 2;
	statswin_sx = term_sx - mapwin_sx - 2;
	statswin_sy = mapwin_sy - 2;

	mapwin_borders = newwin(mapwin_sy + 2, mapwin_sx + 2, 0, 0);
	infowin_borders = newwin(infowin_sy + 2, infowin_sx + 2, mapwin_sy + 2, 0);
	statswin_borders = newwin(statswin_sy + 2, statswin_sx + 2, 0, mapwin_sx + 2);
	fullscreen_textwin_borders = newwin(term_sy, term_sx, 0, 0);
	mapwin = newwin(mapwin_sy, mapwin_sx, 1, 1);
	infowin = newwin(infowin_sy, infowin_sx, mapwin_sy + 3, 1);
	statswin = newwin(statswin_sy, statswin_sx, 1, mapwin_sx + 3);
	fullscreen_textwin = newwin(term_sy - 2, term_sx - 2, 1, 1);

	cursor_ch = CHAR_CURSOR | UI_COLOR_PAIR(F_COLOR_YELLOW, F_COLOR_BLACK) | A_BLINK;
	cursor_x = ui_cur_level->creatures[0]->pos_x - mapwin_x;
	cursor_y = ui_cur_level->creatures[0]->pos_y - mapwin_y;

	for (int i = 0; i < MAX_MESSAGES; ++i)
		messages[i] = 0;
}


// tested
void ui_finish()
{
	wclear(stdscr);
	endwin();
}


Tile* cur_tile;
int i;
// tested
int draw_tile(int x, int y)
{
	if (i == 0)
	{
		++i;
		return ALL_GOOD;
	}
	if (x < 0 || y < 0 || x >= ui_cur_level->size_x || y >= ui_cur_level->size_y || i > ui_cur_level->creatures[0]->sight_distance) return BREAK_HANDLELINE;
	cur_tile = GET_TILE(ui_cur_level, x, y);
	if (cur_tile->creature_id != -1)
	{
		Creature* cur_creature = ui_cur_level->creatures[cur_tile->creature_id];
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_creature->ch);
	}
	else if (cur_tile->items_number > 0)
	{ 
		Item* cur_item = ui_cur_level->items[cur_tile->item_ids[cur_tile->items_number-1]];
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_item->ch);
	}
	else
	{ 
		mvwaddch(mapwin, y - mapwin_y, x - mapwin_x, cur_tile->ch);
	}
	++i;
	if (!(cur_tile->flags & TILE_IS_TRANSPARENT)) return BREAK_HANDLELINE;
	return ALL_GOOD;
}


// tested
void ui_redraw_map()
{
	wclear(mapwin);
	mapwin_x = ui_cur_level->creatures[0]->pos_x - mapwin_sx/2;
	mapwin_y = ui_cur_level->creatures[0]->pos_y - mapwin_sy/2;
	for (int x = mapwin_x; x < mapwin_x + mapwin_sx; ++x)
	{
		i = 0;
		handleline(ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y, x, mapwin_y, &draw_tile);
		i = 0;
		handleline(ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y, x, mapwin_y + mapwin_sy-1, &draw_tile);
	}
	for (int y = mapwin_y; y < mapwin_y + mapwin_sy; ++y)
	{
		i = 0;
		handleline(ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y, mapwin_x, y, &draw_tile);
		i = 0;
		handleline(ui_cur_level->creatures[0]->pos_x, ui_cur_level->creatures[0]->pos_y, mapwin_x + mapwin_sx-1, y, &draw_tile);
	}
	mvwaddch(mapwin, ui_cur_level->creatures[0]->pos_y - mapwin_y, ui_cur_level->creatures[0]->pos_x - mapwin_x, ui_cur_level->creatures[0]->ch);
	wmove(mapwin, mapwin_sy-1, mapwin_sx-1);
	wrefresh(mapwin);
}


void ui_redraw_ui()
{
	switch (ui_mode)
	{
		case UI_MODE_MAIN_VIEW:
			wborder(mapwin_borders, 0, 0, 0, 0, 0, 0, 0, 0);
			wborder(statswin_borders, 0, 0, 0, 0, 0, 0, 0, 0);
			wborder(infowin_borders, 0, 0, 0, 0, 0, 0, 0, 0);
			mvwprintw(mapwin_borders, 0, (mapwin_sx - strlen(ui_cur_level->name))/2 + 1, ui_cur_level->name);
			wrefresh(mapwin_borders);
			wrefresh(statswin_borders);
			wrefresh(infowin_borders);
			ui_redraw_map();
			ui_redraw_stats();
			wclear(infowin);
			wrefresh(infowin);
			break;

		case UI_MODE_FULLSCREEN_TEXT:
			wborder(fullscreen_textwin_borders, 0, 0, 0, 0, 0, 0, 0, 0);
			wrefresh(fullscreen_textwin_borders);
			ui_redraw_fullscreen_text();
			break;

		// make a mode for debugging
	}
}




void ui_message(char* str)
{

}


void ui_popup(uint8_t type, void* form)
{

}


// tested
void ui_input()
{
	int ch = getch();
	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP[i])
		{
			handle_KEY_MOVE_UP();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN[i])
		{
			handle_KEY_MOVE_DOWN();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_LEFT[i])
		{
			handle_KEY_MOVE_LEFT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_RIGHT[i])
		{
			handle_KEY_MOVE_RIGHT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_LEFT[i])
		{
			handle_KEY_MOVE_UP_LEFT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_RIGHT[i])
		{
			handle_KEY_MOVE_UP_RIGHT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN_LEFT[i])
		{
			handle_KEY_MOVE_DOWN_LEFT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_DOWN_RIGHT[i])
		{
			handle_KEY_MOVE_DOWN_RIGHT();
			return;
		}

	for (int i = 0; i < MAX_KEYS_IN_ONE; ++i)
		if (ch == KEY_MOVE_UP_RIGHT[i])
		{
			handle_KEY_MOVE_UP_RIGHT();
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
			return;
		}
}


// tested
void ui_winresize()
{
	getmaxyx(stdscr, term_sy, term_sx);
	mapwin_sx = MAPWIN_SX_RATIO * term_sx - 2;
	mapwin_sy = MAPWIN_SY_RATIO * term_sy - 2;
	infowin_sx = term_sx - 2;
	infowin_sy = term_sy - mapwin_sy - 2;
	statswin_sx = term_sx - mapwin_sx - 2;
	statswin_sy = mapwin_sy - 2;

	mapwin_borders = newwin(mapwin_sy + 2, mapwin_sx + 2, 0, 0);
	infowin_borders = newwin(infowin_sy + 2, infowin_sx + 2, mapwin_sy + 2, 0);
	statswin_borders = newwin(statswin_sy + 2, statswin_sx + 2, 0, mapwin_sx + 2);
	fullscreen_textwin_borders = newwin(term_sy, term_sx, 0, 0);
	mapwin = newwin(mapwin_sy, mapwin_sx, 1, 1);
	infowin = newwin(infowin_sy, infowin_sx, mapwin_sy + 3, 1);
	statswin = newwin(statswin_sy, statswin_sx, 1, mapwin_sx + 3);
	fullscreen_textwin_borders = newwin(term_sy - 2, term_sx - 2, 1, 1);

	ui_redraw_ui();
}




// tested (it doesn't need any test)
void ui_enable_cursor(int reset_pos)
{
	cursor_active = 1;
	if (reset_pos)
	{
		cursor_x = ui_cur_level->creatures[0]->pos_x - mapwin_x;
		cursor_y = ui_cur_level->creatures[0]->pos_y - mapwin_y;
	}
	ui_redraw_ui();
}


// tested (it doesn't need any test)
void ui_disable_cursor()
{
	cursor_active = 0;
	ui_redraw_ui();
}
