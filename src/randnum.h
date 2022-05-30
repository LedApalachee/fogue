#ifndef randnum_h
#define randnum_h

#include <stdint.h>


#define MAX_RANDNUM_MEMBERS 10


typedef struct randset_int64_t
{
	int64_t i; // number itself
	uint8_t p; // probability (percent)
} randset_int64_t;


typedef struct randset_int32_t
{
	int32_t i;
	uint8_t p;
} randset_int32_t;


typedef struct randset_int16_t
{
	int16_t i;
	uint8_t p;
} randset_int16_t;


typedef struct randset_int8_t
{
	int8_t i;
	uint8_t p;
} randset_int8_t;


typedef struct randset_uint64_t
{
	uint64_t i;
	uint8_t p;
} randset_uint64_t;


typedef struct randset_uint32_t
{
	uint32_t i;
	uint8_t p;
} randset_uint32_t;


typedef struct randset_uint16_t
{
	uint16_t i;
	uint8_t p;
} randset_uint16_t;


typedef struct randset_uint8_t
{
	uint8_t i;
	uint8_t p;
} randset_uint8_t;


typedef struct randset_double
{
	double i;
	uint8_t p;
} randset_double;



typedef struct randset_float
{
	float i;
	uint8_t p;
} randset_float;




/*
// if array "set"'s first element is 0, then it chooses number from range_start to range_end (inclusive)
// otherwise it chooses number from "set"
*/

typedef struct randint64_t
{
	int64_t range_start;
	int64_t range_end;
	randset_int64_t set[MAX_RANDNUM_MEMBERS];
} randint64_t;


typedef struct randint32_t
{
	int32_t range_start;
	int32_t range_end;
	randset_int32_t set[MAX_RANDNUM_MEMBERS];
} randint32_t;


typedef struct randint16_t
{
	int16_t range_start;
	int16_t range_end;
	randset_int16_t set[MAX_RANDNUM_MEMBERS];
} randint16_t;


typedef struct randint8_t
{
	int8_t range_start;
	int8_t range_end;
	randset_int8_t set[MAX_RANDNUM_MEMBERS];
} randint8_t;


typedef struct randuint64_t
{
	uint64_t range_start;
	uint64_t range_end;
	randset_uint64_t set[MAX_RANDNUM_MEMBERS];
} randuint64_t;


typedef struct randuint32_t
{
	uint32_t range_start;
	uint32_t range_end;
	randset_uint32_t set[MAX_RANDNUM_MEMBERS];
} randuint32_t;


typedef struct randuint16_t
{
	uint16_t range_start;
	uint16_t range_end;
	randset_uint16_t set[MAX_RANDNUM_MEMBERS];
} randuint16_t;


typedef struct randuint8_t
{
	uint8_t range_start;
	uint8_t range_end;
	randset_uint8_t set[MAX_RANDNUM_MEMBERS];
} randuint8_t;


typedef struct randdouble
{
	double range_start;
	double range_end;
	randset_double set[MAX_RANDNUM_MEMBERS];
} randdouble;


typedef struct randfloat
{
	float range_start;
	float range_end;
	randset_float set[MAX_RANDNUM_MEMBERS];
} randfloat;


#endif
