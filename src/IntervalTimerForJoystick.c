/*
 * File:   IntervalTimerForJoystick.c
 * Author: Shun
 *
 * Created on 2021/11/09, 15:13
 */

#include "IntervalTimer.h"
#include "Interrupt.h"
#include <xc.h>

static void (*_callbackFunction)(void) = NULL;

static void _callbackedFunction(void){
    if(_callbackFunction != NULL){
        (*_callbackFunction)();
    }
    TMR2IF = 0;
}

void IntervalTimerForJoystick_initialize(void){
    T2CONbits.T2CKPS = 0b11; // プリスケーラを64分周で設定
    PR2 = 249; // 16[ms]ごとに割り込み
    
    Interrupt_setTimer2Callback(_callbackedFunction);
}

void IntervalTimerForJoystick_setFrequency(Frequency freq){
    T2CONbits.T2OUTPS = (freq >> 4) - 1; // 16[ms]の定数倍 - 1
}

void IntervalTimerForJoystick_setCallback(void(*callback)(void)){
    _callbackFunction = callback;
}

void IntervalTimerForJoystick_start(void){
    TMR2ON = 1;
    TMR2IE = 1;
}
void IntervalTimerForJoystick_stop(void){
    TMR2ON = 0;
    TMR2IE = 0;
}