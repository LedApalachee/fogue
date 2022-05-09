#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "level.h"


int main(int argc, char** argv)
{
	if (ui_start() == TERMINAL_IS_TOO_SMALL)
	{
		printw("The terminal window is too small.\nThe minimal resolution is %dx%d.\n", TERM_MIN_SX, TERM_MIN_SY);
		getch();
		ui_finish();
		return 0;
	}

	getch();
	ui_finish();
	return 0;
}