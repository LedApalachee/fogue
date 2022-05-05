#include <stdio.h>
#include <stdlib.h>
#include "ui.h"


int main(int argc, char** argv)
{
	if (ui_start() == TERMINAL_IS_TOO_SMALL)
	{
		printw("The terminal window is too small.\nThe minimal resolution is %dx%d.\n", TERM_MIN_X, TERM_MIN_Y);
		getch();
		ui_finish();
		return 0;
	}

	getch();
	ui_finish();
	return 0;
}