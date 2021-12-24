#ifndef ADCCONVERTER_H
#define	ADCCONVERTER_H
#include <stdint.h>

extern void ADConverter_initialize(void);

extern uint8_t ADConverter_getDigitalValue(uint8_t channel);

#endif	/* XC_HEADER_TEMPLATE_H */

