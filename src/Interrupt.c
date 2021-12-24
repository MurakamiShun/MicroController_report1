/*
 * File:   Interrupt.c
 * Author: Shun
 *
 * Created on 2021/10/12, 15:03
 */

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include "Interrupt.h"

static void (*_timer0Callback)(void) = NULL;
void Interrupt_setTimer0Callback(void (*callback)(void)){
    _timer0Callback = callback;
}

static void (*_timer2Callback)(void) = NULL;
void Interrupt_setTimer2Callback(void (*callback)(void)){
    _timer2Callback = callback;
}

static void (*_timer4Callback)(void) = NULL;
void Interrupt_setTimer4Callback(void (*callback)(void)){
    _timer4Callback = callback;
}

static void (*_tactSwitchCallback)(void) = NULL;
void Interrupt_setTactSwitchCallback(void (*callback)(void)){
    _tactSwitchCallback = callback;
}

void __interrupt() Interrupt_interrupt(void){
    if(IOCIF == 1 && _tactSwitchCallback != NULL){
        (*_tactSwitchCallback)();
        IOCIF = 0;
    }
    if(TMR0IF == 1 && _timer0Callback != NULL){
        (*_timer0Callback)();
    }
    if(TMR2IF == 1 &&_timer2Callback != NULL){
        (*_timer2Callback)();
    }
    if(TMR4IF == 1 &&_timer4Callback != NULL){
        (*_timer4Callback)();
    }
}