#ifndef util_h
#define util_h


#define SET(flags, flag) (flags |= flag)
#define RESET(flags, flag) (flags & (~flag))
#define ISSET(flags, flag) (flags & flag)


#endif
