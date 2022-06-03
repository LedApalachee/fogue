#include <handleline.h>
#include "ui.h"
#include "settings.h"
#include "level.h"
#include "creature.h"
#include "item.h"
#include "errors.h"
#include "ascii.h"


void init_pairs()
{
	for (int fg = 0; fg <= COLOR_WHITE; ++fg)
		for (int bg = 0; bg <= COLOR_WHITE; ++bg)
			init_pair(fg*16 + bg, fg, bg);
}

#define UI_GET_PAIR(fg, bg) COLOR_PAIR(fg*16 + bg)


int ui_start()
{
	// "initscr" has already been called in "main"
	start_color();
	refresh();
	mapwin_sx = MAPWIN_SX_RATIO * term_sx;
	mapwin_sy = MAPWIN_SY_RATIO * term_sy;
	logwin_sx = term_sx;
	logwin_sy = term_sy - mapwin_sy;
	statswin_sx = term_sx - mapwin_sx;
	statswin_sy = mapwin_sy;
	mapwin = newwin(mapwin_sy, mapwin_sx, 0, 0);
	logwin = newwin(logwin_sy, logwin_sx, mapwin_sy, 0);
	statswin = newwin(statswin_sy, statswin_sx, 0, mapwin_sx);
	wborder(mapwin, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(logwin, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(statswin, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(mapwin);
	wrefresh(logwin);
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
		++i
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
	mvwaddch(mapwin, level->player->pos_x - mapwin_x, level->player->pos_y - mapwin_y, CHAR_PLAYER);
	wrefresh(mapwin);
}


void ui_add_log(char* message)
{

}


int ui_input()
{
	return ALL_GOOD;
}
