/*
 * File:   TactSwitch.c
 * Author: Shun
 *
 * Created on 2021/10/26, 14:44
 */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "TactSwitch.h"

#define PRESS   (0)
#define RELEASE (1)

bool TactSwitch_isPressedRedButton(void){
    return RB3 == PRESS;
}

bool TactSwitch_isPressedGreenButton(void){
    return RB4 == PRESS;
}

bool TactSwitch_isPressedBlueButton(void){
    return RA0 == PRESS;
}

void TactSwitch_initialize(void){
    ANSA0 = 0; // PortA0をデジタルピンとする(青)
    ANSB3 = 0; // PortB3をデジタルピンとする(赤)
    ANSB4 = 0; // PortB4をデジタルピンとする(緑)
    
    TRISA0 = 1; // PortA0を入力端子とする(青)
    TRISB3 = 1; // PortB3を入力端子とする(赤)
    TRISB4 = 1; // PortB4を入力端子とする(緑)
}