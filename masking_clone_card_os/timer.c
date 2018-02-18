/*
 * timer.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */
#include "timer.h"

// configuration of Output Compare Match A Interrupt
void setup_etu(void){
	//TCCR2B – Timer/Counter Control Register B
	TCCR1B |= (1 << CS10);	// no prescaler

	// OCR2A – Output Compare Register A
	OCR1AH = 0x01;		// interrupt after 379 cycles
	OCR1AL = 0x74;	// interrupt after 379 cycles
	//OCR1AH = 1;		// interrupt after 379 cycles
	//OCR1AL = 0x7b;	// interrupt after 379 cycles

	// TIMSK1 – Timer/Counter1 Interrupt Mask Register: Output Compare Match A Interrupt Enable
	//TIMSK1 |= (1 << OCF1A);

	//	CTC: Clear Timer on Compare Match
	TCCR1B |= (1 << WGM12);
}

// enable timer 1 (Output Compare Match A)
void enable_etu_TIMER1(void){
	// TIMSK1 – Timer/Counter1 Interrupt Mask Register: Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCF1A);
}

// disable timer 1 (Output Compare Match A)
void disable_etu_TIMER1(void){
	// TIMSK1 – Timer/Counter1 Interrupt Mask Register: Output Compare Match A Interrupt Enable
	TIMSK1 &= ~(1 << OCF1A);
}


