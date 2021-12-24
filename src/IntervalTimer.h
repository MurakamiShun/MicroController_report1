#ifndef INTERVAL_TIMER_H
#define	INTERVAL_TIMER_H

// 割り込み頻度[ms]
typedef enum {
    // 頻繁
    FREQUENTLY = 16,
    // ときどき
    SOMETIMES = 96,
    // めったにしない
    RARELY = 256
} Frequency;

#endif	/* INTERVAL_TIMER_H */