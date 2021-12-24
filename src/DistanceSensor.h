#ifndef DISTANCE_SENSOR_H
#define	DISTANCE_SENSOR_H
#include <stdint.h>
#include "IntervalTimer.h"

extern void DistanceSensor_initialize(void);

extern void DistanceSensor_setCallbackFunction(void(*callback)(uint16_t*));

extern void DistanceSensor_setFrequency(Frequency);

#endif	/* DISTANCE_SENSOR_H */
