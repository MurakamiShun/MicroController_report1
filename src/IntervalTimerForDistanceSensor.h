#ifndef INTERVAL_TIMER_FOR_DISTANCE_SENSOR_H
#define	INTERVAL_TIMER_FOR_DISTANCE_SENSOR_H
#include "IntervalTimer.h"

extern void IntervalTimerForDistanceSensor_initalize(void);

extern void IntervalTimerForDistanceSensor_setFrequency(Frequency freq);

extern void IntervalTimerForDistanceSensor_setCallback(void(*callback)(void));

extern void IntervalTimerForDistanceSensor_start(void);
extern void IntervalTimerForDistanceSensor_stop(void);

#endif	/* INTERVAL_TIMER_FOR_DISTANCE_SENSOR_H */