#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "level.h"
#include "errors.h"
#include "util.h"
#include "ascii.h"


// current task: make showcase with editable map and some objects on it


int main(int argc, char** argv)
{
	initscr();
	getmaxyx(stdscr, term_sy, term_sx);
	if (term_sx < TERM_MIN_SX || term_sy < TERM_MIN_SY)
	{
		printw("The terminal window is too small.\nThe minimal resolution is %dx%d.\n", TERM_MIN_SX, TERM_MIN_SY);
		getch();
		ui_finish();
		return 0;
	}
	ui_start();

	getch();
	ui_finish();
	return 0;
}
