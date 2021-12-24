#ifndef INTERVAL_TIMER_FOR_JOYSTICK_H
#define	INTERVAL_TIMER_FOR_JOYSTICK_H
#include "IntervalTimer.h"

extern void IntervalTimerForJoystick_initialize(void);

extern void IntervalTimerForJoystick_setFrequency(Frequency freq);

extern void IntervalTimerForJoystick_setCallback(void(*callback)(void));

extern void IntervalTimerForJoystick_start(void);
extern void IntervalTimerForJoystick_stop(void);

#endif	/* INTERVAL_TIMER_FOR_JOYSTICK_H */