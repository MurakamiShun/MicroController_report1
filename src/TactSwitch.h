#ifndef TACT_SWITCH_H
#define	TACT_SWITCH_H
#include <stdbool.h>

extern void TactSwitch_initialize(void);

extern bool TactSwitch_isPressedRedButton(void);
extern bool TactSwitch_isPressedGreenButton(void);
extern bool TactSwitch_isPressedBlueButton(void);

#endif	/* XC_HEADER_TEMPLATE_H */

