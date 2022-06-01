#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "level.h"
#include "errors.h"
#include "util.h"


int main(int argc, char** argv)
{
	if (ui_start() == TERMINAL_IS_TOO_SMALL)
	{
		printw("The terminal window is too small.\nThe minimal resolution is %dx%d.\n", TERM_MIN_SX, TERM_MIN_SY);
		getch();
		ui_finish();
		return 0;
	}


	Level* level = create_blank_level(20, 20);


	Creature c;
	c.id = 1;
	c.type = 1;
	c.name = "blarg";
	c.ch = 'B';
	c.pos_x = 0;
	c.pos_y = 0;
	c.flags = 0;


	// current task: test functions from level.c
	// next task: test map displaying functions and start implementing user input


	getch();
	ui_finish();
	delete_level(level, 1, 0);
	return 0;
}
