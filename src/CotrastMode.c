/*
 * File:   CotrastMode.c
 * Author: Shun
 *
 * Created on 2021/12/24, 5:50
 */
#include "ContrastMode.h"
#include "DotMatrixDisplay.h"
#include "DistanceSensor.h"

static uint8_t _current_contrast = 1;

static void _changeDistanceSensor(uint16_t* d){
    _current_contrast = (uint8_t)((*d) >> 8);
}

void ContrastMode_initialize(void){
    DistanceSensor_setCallbackFunction(_changeDistanceSensor);
    DistanceSensor_setFrequency(FREQUENTLY);
}

void ContrastMode_update(void){
    DotMatrixDisplay_hide();
    DotMatrixDisplay_setNumberPattern(_current_contrast);
    DotMatrixDisplay_setContrast(_current_contrast);
    DotMatrixDisplay_show();
}