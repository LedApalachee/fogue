#include "ui.h"
#include "settings.h"
#include <handleline.h>

int ui_start()
{
	initscr();
	refresh();
	getmaxyx(stdscr, termsize_y, termsize_x);
	if (termsize_x < TERM_MIN_X || termsize_y < TERM_MIN_Y) return TERMINAL_IS_TOO_SMALL;
	mapwin_sx = MAP_WIN_SIZE_X_RATIO * termsize_x;
	mapwin_sy = MAP_WIN_SIZE_Y_RATIO * termsize_y;
	logwin_sx = termsize_x;
	logwin_sy = termsize_y - mapwin_sy;
	statswin_sx = termsize_x - mapwin_sx;
	statswin_sy = mapwin_sy;
	map_win = newwin(mapwin_sy, mapwin_sx, 0, 0);
	log_win = newwin(logwin_sy, logwin_sx, mapwin_sy, 0);
	stats_win = newwin(statswin_sy, statswin_sx, 0, mapwin_sx);
	wborder(map_win, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(log_win, 0, 0, 0, 0, 0, 0, 0, 0);
	wborder(stats_win, 0, 0, 0, 0, 0, 0, 0, 0);
	wrefresh(map_win);
	wrefresh(log_win);
	wrefresh(stats_win);
	return ALL_GOOD;
}


Level* cur_level;
void see_tile(int x, int y)
{
	// ...
}


void ui_redraw_map(Level* level)
{
	wclear(map_win);
	cur_level = level;
}


void ui_finish()
{
	endwin();
}
