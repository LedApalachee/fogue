#ifndef ui_h
#define ui_h

#include <curses.h>
#include "level.h"


#define MAPWIN_SX_RATIO 0.75
#define MAPWIN_SY_RATIO 0.8

#define TERM_MIN_SX 80
#define TERM_MIN_SY 25

#define UI_COLOR_PAIR(fg, bg) COLOR_PAIR(fg*16 + bg)

#define MAX_MESSAGES 100


int term_sx, term_sy;
int mapwin_sx, mapwin_sy;
int mapwin_x, mapwin_y; // coordinates of begining of the map window (they also can be negative)
int infowin_sx, infowin_sy;
int statswin_sx, statswin_sy;
WINDOW* mapwin;
WINDOW* statswin;
WINDOW* infowin;

char* messages[MAX_MESSAGES]; // stack of messages that appear in logwin

int quit; // if it's TRUE, the game will end


int ui_start();
void ui_finish();
void ui_redraw_map(Level* level);
void ui_message(char* str);
void ui_popup(uint8_t type, void* content); // depending on popup type, a content format may differ from others
void ui_input(Level* level); // doesn't just read the pressed key but also performs related actions
void ui_winresize();


#endif
