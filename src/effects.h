#ifndef effects_h
#define effects_h

#include <stdint.h>


typedef struct Effect
{
	uint16_t type;
	uint16_t time_left;
} Effect;


typedef enum EffectType
{
	EFFECT_NONE,

	// physiological
	EFFECT_BURNING,
	EFFECT_BLEEDING,
	EFFECT_FAINT,
	EFFECT_BLIND,

	// behavioral-psychological
	EFFECT_CONFUSED,
	EFFECT_TERRIFIED,
	EFFECT_ENCOURAGED,
	EFFECT_LOSTMINDED

	// there will be more effects

} EffectType;


#endif