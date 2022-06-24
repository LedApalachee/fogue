#ifndef ui_h
#define ui_h

#include <curses.h>


#define MAPWIN_SX_RATIO 0.75
#define MAPWIN_SY_RATIO 0.8

#define TERM_MIN_SX 80
#define TERM_MIN_SY 25

#define UI_COLOR_PAIR(fg, bg) COLOR_PAIR(fg*16 + bg)

#define MAX_MESSAGES 100

#define UI_MODE_MAIN_MENU 0
#define UI_MODE_MAIN_VIEW 1 // the map, the info win and the player's stats
#define UI_MODE_FULLSCREEN_TEXT 2


int term_sx, term_sy;
int mapwin_sx, mapwin_sy;
int mapwin_x, mapwin_y; // coordinates of begining of the map window (they also can be negative)
int infowin_sx, infowin_sy;
int statswin_sx, statswin_sy;

WINDOW* mapwin;
WINDOW* mapwin_borders;
WINDOW* statswin;
WINDOW* statswin_borders;
WINDOW* infowin;
WINDOW* infowin_borders;
WINDOW* fullscreen_textwin;
WINDOW* fullscreen_textwin_borders;


int cursor_active;
int cursor_x, cursor_y;
chtype cursor_ch;

char* messages[MAX_MESSAGES]; // stack of messages that appear in infowin

int ui_mode;

int quit; // if it's TRUE, this is signal for the game to shutdown

struct Level* ui_cur_level;

char* ui_fullscreen_text;




void ui_start();
void ui_finish();

void ui_redraw_map(); // redraws map, the objects and player
void ui_redraw_stats(); // redraws player's info
void ui_redraw_fullscreen_text();
void ui_redraw_ui();

void ui_message(char* str); // prints it in the info win and saves it in "messages"
void ui_popup(uint8_t type, void* form); // depending on popup type, a content format may differ from others
void ui_input(); // doesn't just read the pressed key but also performs related actions
char* ui_read_str();
void ui_winresize();

void ui_enable_cursor(int reset_pos); // if "reset_pos" is TRUE, the cursor takes its initial position
void ui_disable_cursor();


#endif
