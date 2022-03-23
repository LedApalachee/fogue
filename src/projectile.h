#ifndef projectile_h
#define projectile_h


typedef struct ProjectileInfo
{
	struct Entity* item; // which item is ballisted
	int dir_x, dir_y; // these are needed to plot the line (Bresenham's line algorithm)
	int energy; // when energy <= 0, projectile stops moving; loss of energy equals to number of passed tiles
	int speed; // how many tiles it passes per turn
} ProjectileInfo;


void projectile_take_turn(struct Level* level, struct Entity* projectile);


#endif