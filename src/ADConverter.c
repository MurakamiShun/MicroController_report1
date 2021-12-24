#define _XTAL_FREQ   (4000000UL)

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "ADConverter.h"

void ADConverter_initialize(void){
    TRISA2 = 1; // RA2Portを入力端子とする
    TRISA3 = 1; // RA3Portを入力端子とする
    
    ANSA2 = 1; // RA2Portをアナログ端子とする
    ANSA3 = 1; // RA3Portをアナログ端子とする
    
    ADCON1bits.ADCS = 0b100; // AD変換を1usにする
    /* ADCS2 = 1; ADCS1 = 0; ADCS0 = 0; */
    
    ADPREF0 = 0; // AD変換の上限電圧
    ADPREF1 = 0;
    ADNREF = 0; // AD変換の下限電圧
    
    ADFM = 0; // 左詰め
}

uint8_t ADConverter_getDigitalValue(uint8_t channel){
    ADCON0bits.CHS = channel;
    ADON = 1;
    __delay_us(2);
    GO = 1;
    while(GO == 1);
    return ADRESH;
}