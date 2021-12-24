#ifndef JOYSTICK_H
#define	JOYSTICK_H
#include <stdint.h>
#include "IntervalTimer.h"

extern void Joystick_initialize(void);

extern void Joystick_setCallbackFunction(void(*callback)(uint8_t*, uint8_t*));

extern void Joystick_setFrequency(Frequency);

#endif	/* JOYSTICK_H */

