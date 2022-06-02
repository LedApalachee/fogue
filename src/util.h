#ifndef util_h
#define util_h


#define SETF(flags, flag) (flags |= flag)
#define RESETF(flags, flag) (flags &= (~flag))
#define ISFSSET(flags, flag) (flags & flag)


#endif
