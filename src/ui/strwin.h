#ifndef STRWIN_H
#define STRWIN_H

#include <stdint.h>


typedef struct StringWin
{
	int sx_b, sy_b; // size of borders
	int sx, sy;
	int len;
	char* str;
	int seek;
	uint8_t flags;
} StringWin;


// flags
#define STRWIN_BORDERED 1


StringWin* strwin_new(int sx, int sy, char* str, uint8_t flags);
void strwin_new_str(StringWin* strwin, char* str);
void strwin_append(StringWin* strwin, char* str);
void strwin_cut(StringWin* strwin, int from, int to);
void strwin_draw(StringWin* strwin, int x, int y);
void strwin_free(StringWin* strwin);


#endif
