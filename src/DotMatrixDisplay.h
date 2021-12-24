#ifndef DOTMATRIXDISPLAY_H
#define	DOTMATRIXDISPLAY_H

#include <stdint.h>

typedef enum {
    SPACE                    = 0x00, // 全消灯
    UPPER_RIGHT_CORNER       = 0x01, // ┓形 
    UPPER_LEFT_CORNER        = 0x02, // ┏形
    LOWER_RIGHT_CORNER       = 0x03, // ┛形
    LOWER_LEFT_CORNER        = 0x04, // ┗形
    COUNTER_CLOCKWISE_TCROSS = 0x05, // ┣形
    TCROSS                   = 0x06, // ┳形
    CLOCKWISE_TCROSS  = 0x07, // ┫形
    INVERT_TCROSS     = 0x08, // ┻形
    CROSS             = 0x09, // ╋形
    RECTANGLE         = 0x0A, // 四角形
    ARGYLE            = 0x0B, // ひし形
    X_SHAPED          = 0x0C, // ×
    V_SHAPED          = 0x0D, // V字
    UPPER_TRIANGLE    = 0x0E, // 上向き三角
    RIGHT_TRIANGLE    = 0x0F, // 右向き三角
    LOWER_TRIANGLE    = 0x10, // 下向き三角
    LEFT_TRIANGLE     = 0x11, // 左向き三角
    DOT               = 0x12, // ・
    ALL_LIGHTING      = 0x13, // 全点灯
    UPPER_ARROW       = 0x14, // 上向き矢印
    UPPER_RIGHT_ARROW = 0x15, // 右上向き矢印
    RIGHT_ARROW       = 0x16, // 右向き矢印
    LOWER_RIGHT_ARROW = 0x17, // 右下向き矢印
    LOWER_ARROW       = 0x18, // 下向き矢印
    LOWER_LEFT_ARROW  = 0x19, // 左下向き矢印
    LEFT_ARROW        = 0x1A, // 左向き矢印
    UPPER_LEFT_ARROW  = 0x1B, // 左上向き矢印
} ShapeType;

extern void DotMatrixDisplay_initialize(void);

extern void DotMatrixDisplay_setPattern(ShapeType type);

extern void DotMatrixDisplay_setNumberPattern(uint8_t value);

extern void DotMatrixDisplay_setContrast(uint8_t value);

extern void DotMatrixDisplay_show(void);

extern void DotMatrixDisplay_hide(void);

#endif	/* XC_HEADER_TEMPLATE_H */
