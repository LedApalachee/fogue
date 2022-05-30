#ifndef ui_h
#define ui_h

#include <curses.h>
#include "level.h"


#define MAPWIN_SX_RATIO 0.75
#define MAPWIN_SY_RATIO 0.85

#define TERM_MIN_SX 80
#define TERM_MIN_SY 25

#define MAPWIN_PLAYER_X mapwin_sx/2
#define MAPWIN_PLAYER_y mapwin_sy/2


int term_sx, term_sy;
int mapwin_sx, mapwin_sy;
int mapwin_x, mapwin_y; // coordinates of begining of the map window (they also can be negative)
int logwin_sx, logwin_sy;
int statswin_sx, statswin_sy;
WINDOW* mapwin;
WINDOW* statswin;
WINDOW* logwin;

int ui_start();
void ui_finish();
void ui_redraw_map(Level* level);
void ui_add_log(char* message);
int ui_input();


#endif
