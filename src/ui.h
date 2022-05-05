#ifndef ui_h
#define ui_h

#include <curses.h>
#include "level.h"


#define MAP_WIN_SIZE_Y_RATIO 0.85
#define MAP_WIN_SIZE_X_RATIO 0.6

#define TERM_MIN_X 80
#define TERM_MIN_Y 25


int termsize_x, termsize_y;
int mapwin_sx, mapwin_sy;
int logwin_sx, logwin_sy;
int statswin_sx, statswin_sy;
WINDOW* map_win;
WINDOW* stats_win;
WINDOW* log_win;

int ui_start();
void ui_redraw_map(Level* level);
void ui_finish();
void ui_add_log(char* message);


#define ALL_GOOD 0
#define TERMINAL_IS_TOO_SMALL 1


#endif