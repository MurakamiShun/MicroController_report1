/*
 * File:   IntervalTimerForDMD.c
 * Author: Shun
 *
 * Created on 2021/10/12, 14:53
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "IntervalTimerForDMD.h"
#include "Interrupt.h"

#define _125us (131)

static void (*_callbackFunction)(void) = NULL;

static void _callbackedFunction(void){
    if(_callbackFunction != NULL){
        (*_callbackFunction)(); // 呼び出したい関数の呼び出し
    }
    TMR0 = _125us;          // 125usでオーバーフローさせる
    TMR0IF = 0;             // 割り込みフラグクリア
}

void IntervalTimerForDMD_initialize(void){
    TMR0CS = 0;    // Fosc/4をクロックとして使用する
    PSA = 1;       // Prescalarで分周しない
    TMR0 = _125us; // 125回カウントしたらオーバフローさせるようにする
    Interrupt_setTimer0Callback(_callbackedFunction); // 割込み時に呼び出すコールバック関数を設定する
}

void IntervalTimerForDMD_setCallback(void(*callback)(void)){
    _callbackFunction = callback;
}

void IntervalTimerForDMD_start(void){
    TMR0IE = 1;
}

void IntervalTimerForDMD_stop(void){
    TMR0IE = 0;
}