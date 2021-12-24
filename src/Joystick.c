#include <xc.h>
#include <stdint.h>
#include "ADConverter.h"
#include "IntervalTimerForJoystick.h"

#define _HORIZONTAL_CHANNEL (2) // 水平方向のチャネル番号
#define _VERTICAL_CHANNEL   (3) // 垂直方向のチャネル番号

static void (*_callbackFunction)(uint8_t*, uint8_t*) = NULL;

static void _measure(void){
    uint8_t h = ADConverter_getDigitalValue(_HORIZONTAL_CHANNEL);
    uint8_t v = ADConverter_getDigitalValue(_VERTICAL_CHANNEL);
    if(_callbackFunction != NULL){
        (*_callbackFunction)(&h, &v);
    }
}

void Joystick_initialize(void){
    ADConverter_initialize();
    
    IntervalTimerForJoystick_initialize();
    IntervalTimerForJoystick_setFrequency(RARELY);
    IntervalTimerForJoystick_setCallback(_measure);
    IntervalTimerForJoystick_start();
}

void Joystick_setFrequency(Frequency freq){
    IntervalTimerForJoystick_setFrequency(freq);
}

void Joystick_setCallbackFunction(void(*callback)(uint8_t*, uint8_t*)){
    _callbackFunction = callback;
}