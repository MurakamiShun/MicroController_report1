/*
 * File:   DistanceSensor.c
 * Author: Shun
 *
 * Created on 2021/11/16, 14:46
 */

#include <stdint.h>
#include <xc.h>
#include "IntervalTimerForDistanceSensor.h"
#include "ADConverter.h"
#include "DistanceSensor.h"

#define _DISTANCE_SENSOR_CHANNEL (1)

static const uint16_t _DISTANCE_TABLE[] = {
    1949, 1912, 1875, 1838, 1801, 1765, 1728, 1691, 1654, 1617, 1580, 1544, 1507, 1470, 1433, 1396,
    1360, 1323, 1286, 1249, 1212, 1175, 1139, 1102, 1065, 1028, 991, 954, 918, 881, 844, 807,
    738, 718, 674, 659, 644, 629, 614, 563, 553, 544, 534, 525, 515, 505, 468, 461,
    454, 447, 440, 434, 427, 420, 413, 406, 400, 358, 353, 349, 345, 341, 336, 332,
    328, 323, 319, 315, 311, 306, 302, 281, 278, 275, 273, 270, 267, 264, 262, 259,
    256, 253, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 213, 211,
    209, 207, 205, 203, 201, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163,
    162, 161, 160, 159, 158, 157, 156, 155, 155, 154, 153, 152, 151, 150, 149, 147,
    146, 145, 144, 143, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132,
    131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 110, 110, 109, 109,
    108, 107, 107, 106, 106, 105, 105, 104, 103, 103, 102, 102, 101, 100, 100, 99,
    99, 98, 96, 95, 95, 94, 94, 93, 93, 92, 92, 91, 91, 90, 89, 89,
    88, 88, 87, 87, 86, 86, 85, 84, 84, 83, 83, 82, 82, 81, 81, 80,
    79, 79, 78, 78, 84, 83, 82, 81, 80, 79, 78, 77, 77, 76, 75, 74,
    73, 72, 71, 70, 69, 68, 67, 66, 65, 65, 64, 63, 62, 61, 60, 59,
    58, 57, 56, 55, 54, 53, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44,
};

static void (*_callbackFunction)(uint16_t*) = NULL;

static void _measure(void){
    uint8_t d_v = ADConverter_getDigitalValue(_DISTANCE_SENSOR_CHANNEL);
    uint16_t d = _DISTANCE_TABLE[d_v];
    if(_callbackFunction != NULL){
        (*_callbackFunction)(&d);
    }
}

void DistanceSensor_initialize(void){
    ADConverter_initialize();
    
    IntervalTimerForDistanceSensor_initalize();
    IntervalTimerForDistanceSensor_setFrequency(RARELY);
    IntervalTimerForDistanceSensor_setCallback(_measure);
    IntervalTimerForDistanceSensor_start();
}

void DistanceSensor_setCallbackFunction(void(*callback)(uint16_t*)){
    _callbackFunction = callback;
}

void DistanceSensor_setFrequency(Frequency freq){
    IntervalTimerForDistanceSensor_setFrequency(freq);
}