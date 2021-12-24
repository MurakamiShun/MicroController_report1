#define _XTAL_FREQ 4000000UL
#include <xc.h>
#include <stdbool.h>
#include "MemoryGameMode.h"
#include "DotMatrixDisplay.h"
#include "Joystick.h"
#define ARROW_NUM (4)
static uint8_t _latest_h, _latest_v;

static uint8_t _correct_arrows[ARROW_NUM];
static uint8_t _next_arrow = 0;
static uint8_t _correct_count = 0;

static ShapeType _arrow_shapes[4] = {
UPPER_ARROW,
LOWER_ARROW,
RIGHT_ARROW,
LEFT_ARROW
};

static uint32_t _xorshift32(void) {
  static uint32_t y = 2463534242;
  y = y ^ (y << 13); y = y ^ (y >> 17);
  return y = y ^ (y << 5);
}

static void _changeJoystick(uint8_t* h, uint8_t* v){
    _latest_h = ((*h) >> 5);
    _latest_v = ((*v) >> 5);
}

void MemoryGameMode_initialize(void){
    Joystick_setCallbackFunction(_changeJoystick);
    Joystick_setFrequency(FREQUENTLY);
    
    _next_arrow = 0;
    _correct_count = 0;
    
    // 覚える方向の表示
    for(uint8_t i = 0; i < ARROW_NUM; ++i){
        _correct_arrows[i] = _xorshift32() & 3;
        DotMatrixDisplay_hide();
        DotMatrixDisplay_setPattern(_arrow_shapes[_correct_arrows[i]]);
        DotMatrixDisplay_show();
        __delay_ms(300);
        DotMatrixDisplay_hide();
        DotMatrixDisplay_setPattern(SPACE);
        DotMatrixDisplay_show();
        __delay_ms(100);
    }
}

void MemoryGameMode_update(void){
    static bool reset_neutral = true;
    if(_next_arrow >= ARROW_NUM){
        DotMatrixDisplay_setNumberPattern(_correct_count);
        return;
    }
    if(reset_neutral){
        if(_latest_v == 7){ // 上
            reset_neutral = false;
            if(_correct_arrows[_next_arrow] == 0){
                 DotMatrixDisplay_setPattern(UPPER_ARROW);
                 _correct_count++;
            }
            else{
                DotMatrixDisplay_setPattern(X_SHAPED);
            }
            _next_arrow++;
        }
        else if(_latest_v == 0){ // 下
            reset_neutral = false;
            if(_correct_arrows[_next_arrow] == 1){
                 DotMatrixDisplay_setPattern(LOWER_ARROW);
                 _correct_count++;
            }
            else{
                DotMatrixDisplay_setPattern(X_SHAPED);
            }
            _next_arrow++;
        } 
        else if(_latest_h == 7){ // 右
            reset_neutral = false;
            if(_correct_arrows[_next_arrow] == 2){
                 DotMatrixDisplay_setPattern(RIGHT_ARROW);
                 _correct_count++;
            }
            else{
                DotMatrixDisplay_setPattern(X_SHAPED);
            }
            _next_arrow++;
        }
        else if(_latest_h == 1){ // 左
            reset_neutral = false;
            if(_correct_arrows[_next_arrow] == 3){
                 DotMatrixDisplay_setPattern(LEFT_ARROW);
                 _correct_count++;
            }
            else{
                DotMatrixDisplay_setPattern(X_SHAPED);
            }
            _next_arrow++;
        }
    }
    else if(_latest_h >= 2 && _latest_h <= 5 && _latest_v >= 2 && _latest_v <= 5){ // 真ん中
        reset_neutral = true;
    }
}