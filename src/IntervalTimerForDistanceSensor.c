/*
 * File:   IntervalTimerForJoystick.c
 * Author: Shun
 *
 * Created on 2021/11/09, 15:13
 */
#include <xc.h>
#include <stdint.h>
#include "IntervalTimerForDistanceSensor.h"
#include "Interrupt.h"

static void (*_callbackFunction)(void) = NULL;

static void _callbackedFunction(void){
    if(_callbackFunction != NULL){
        (*_callbackFunction)();
    }
    TMR4IF = 0;
}

void IntervalTimerForDistanceSensor_initalize(void){
    T4CONbits.T4CKPS = 0b11; // プリスケーラを64分周で設定
    PR4 = 249; // 16[ms]ごとに割り込み
    
    Interrupt_setTimer4Callback(_callbackedFunction);
}

void IntervalTimerForDistanceSensor_setFrequency(Frequency freq){
    T4CONbits.T4OUTPS = (freq >> 4) - 1; // 16[ms]の定数倍 - 1
}

void IntervalTimerForDistanceSensor_setCallback(void(*callback)(void)){
    _callbackFunction = callback;
}

void IntervalTimerForDistanceSensor_start(void){
    TMR4ON = 1;
    TMR4IE = 1;
}
void IntervalTimerForDistanceSensor_stop(void){
    TMR4ON = 0;
    TMR4IE = 0;
}