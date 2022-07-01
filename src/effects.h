#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdint.h>


typedef struct Effect
{
	uint16_t type;
	int16_t time_left; // if this var equals -1, the effect is considered eternal
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
	EFFECT_MINDLOST,

	// magical
	EFFECT_INVISIBLE,
	EFFECT_LEVITATING
} EffectType;


#endif
