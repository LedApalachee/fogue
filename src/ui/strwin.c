#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "ui.h"
#include "strwin.h"
#include "../errors.h"


StringWin* strwin_new(int sx, int sy, char* str, uint8_t flags)
{
	StringWin* strwin = (StringWin*)malloc(sizeof(StringWin));
	if (flags & STRWIN_BORDERED)
	{
		strwin->sx_b = sx;
		strwin->sy_b = sy;
		strwin->sx = sx-2;
		strwin->sy = sy-2;
	}
	else
	{
		strwin->sx = strwin->sx_b = sx;
		strwin->sy = strwin->sy_b = sy;
	}
	int len = strlen(str);
	strwin->str = (char*)malloc(sizeof(char) * len + sizeof(char));
	strcpy(strwin->str, str);
	strwin->str[len] = '\0';
	strwin->len = len;
	strwin->flags = flags;
	return strwin;
}


void strwin_new_str(StringWin* strwin, char* str)
{
	free(strwin->str);
	int len = strlen(str);
	strwin->str = (char*)malloc(sizeof(char) * (len + 1));
	strcpy(strwin->str, str);
	strwin->str[len] = '\0';
	strwin->len = len;
}


void strwin_append(StringWin* strwin, char* str)
{
	int len = strlen(str);
	strwin->str = realloc(strwin->str, sizeof(char) * (strwin->len + len + 1));
	for (int i = 0; i < len; ++i)
		strwin->str[strwin->len + i] = str[i];
	strwin->len += len;
	strwin->str[strwin->len] = '\0';
}


void strwin_cut(StringWin* strwin, int from, int to)
{
	if (to >= strwin->len) to = strwin->len-1;
	for (int i = 1; to + i < strwin->len; ++i)
		strwin->str[from + i - 1] = strwin->str[to + i];
	strwin->str = realloc(strwin->str, sizeof(char) * (strwin->len - to + from));
	strwin->len += from - to - 1;
	strwin->str[strwin->len] = '\0';
}


void strwin_draw(StringWin* strwin, int x, int y)
{
	if (x + strwin->sx_b > term_sx || y + strwin->sy_b > term_sy)
		return WIN_CROSSES_TERMINAL_BOUNDS;

	WINDOW* strwinwin;
	WINDOW* strwinwin_b;
	if (strwin->flags & STRWIN_BORDERED)
	{
		strwinwin_b =  newwin(strwin->sy_b, strwin->sx_b, y, x);
		strwinwin = newwin(strwin->sy, strwin->sx, y+1, x+1);
		refresh();
		wborder(strwinwin_b, 0, 0, 0, 0, 0, 0, 0, 0);
	}
	else
	{
		strwinwin_b = 0;
		strwinwin = newwin(strwin->sy, strwin->sx, y, x);
		refresh();
	}
}


void strwin_free(StringWin* strwin)
{
	free(strwin->str);
	strwin->len = 0;
}
