#ifndef INTERRUPT_H
#define	INTERRUPT_H

extern void __interrupt() Interrupt_interrupt(void);

extern void Interrupt_setTimer0Callback(void(*callback)(void));
extern void Interrupt_setTimer2Callback(void(*callback)(void));
extern void Interrupt_setTimer4Callback(void(*callback)(void));

#endif	/* INTERRUPT_H */