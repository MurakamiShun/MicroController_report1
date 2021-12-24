// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#define _XTAL_FREQ (4000000UL)
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "DotMatrixDisplay.h"
#include "TactSwitch.h"
#include "Joystick.h"
#include "ContrastMode.h"
#include "MemoryGameMode.h"
#include "DistanceSensor.h"

typedef enum {
    ContrastMode = 0,
    MemoryGameMode = 1,
    ModeSelect = 2
} Mode;

static void (*_mode_initializers[2])(void) = {
    ContrastMode_initialize,
    MemoryGameMode_initialize
};

Mode _mode_select(void){
    static Mode _selected_mode = ContrastMode;
    static uint16_t blink_time = 0;
    
    // モード番号表示
    if(blink_time > 32768) DotMatrixDisplay_setNumberPattern((uint8_t)_selected_mode);
    else DotMatrixDisplay_setPattern(SPACE);
    blink_time+=32;
    
    
    if(TactSwitch_isPressedRedButton()){
        __delay_ms(1); // チャタリング防止
        while(TactSwitch_isPressedRedButton());
        _selected_mode = ContrastMode;
    }
    else if(TactSwitch_isPressedGreenButton()){
        __delay_ms(1); // チャタリング防止
        while(TactSwitch_isPressedGreenButton());
        _selected_mode = MemoryGameMode;
    }
    if(TactSwitch_isPressedBlueButton()){
        __delay_ms(1); // チャタリング防止
        while(TactSwitch_isPressedBlueButton());
        (*(_mode_initializers[_selected_mode]))();
        return _selected_mode;
    }
    
    return ModeSelect;
}

void main(void) {
    /* 内部オシレータの速度を4[MHz]とする */
    IRCF0 = 1;
    IRCF1 = 0;
    IRCF2 = 1;
    IRCF3 = 1;
    
    GIE = 1; // 割り込み許可
    PEIE = 1;
    
    /* LCD を制御しないようにする */
    LCDEN = 0;
    
    TactSwitch_initialize();
    DotMatrixDisplay_initialize();
    DotMatrixDisplay_show();
    Joystick_initialize();
    DistanceSensor_initialize();
    
    Mode current_mode = ModeSelect;
    
    while(true){
        // モードリセット
        if(TactSwitch_isPressedBlueButton()){
            __delay_ms(1); // チャタリング防止
            while(TactSwitch_isPressedBlueButton());
            current_mode = ModeSelect;
        }
        switch(current_mode){
            case ContrastMode:
                ContrastMode_update();
                break;
            case MemoryGameMode:
                MemoryGameMode_update();
                break;
            case ModeSelect:
                current_mode = _mode_select();
                break;
        }
    }
    return;
}
