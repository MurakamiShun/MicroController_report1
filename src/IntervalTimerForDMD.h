#ifndef INTERVAL_TIMER_FOR_DMD_H
#define	INTERVAL_TIMER_FOR_DMD_H
#include <stdint.h>
#include <stdbool.h>

extern void IntervalTimerForDMD_initialize(void);

extern void IntervalTimerForDMD_setCallback(void(*callback)(void));

extern void IntervalTimerForDMD_start(void);

extern void IntervalTimerForDMD_stop(void);

#endif	/* INTERVAL_TIMER_FOR_DMD_H */

