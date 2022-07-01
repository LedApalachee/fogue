#ifndef UTIL_H
#define UTIL_H


#define SETF(flags, flag) (flags |= flag)
#define RESETF(flags, flag) (flags &= (~flag))
#define ISFSET(flags, flag) (flags & flag)


#define SWAP(a, b, type) \
{						 \
	type t = a;			 \
	a = b;				 \
	b = t;				 \
}




void print_creature(struct Creature* creature);
void print_item(struct Item* item);
void print_tile(struct Level* level, int x, int y);


#endif
