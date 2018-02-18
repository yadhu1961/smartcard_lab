/*
 * timer.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */
#include "interrupts.h"

// configuration of Output Compare Match A Interrupt
void setup_etu(void){
	//TCCR2B – Timer/Counter Control Register B
	TCCR1B |= (1 << CS10);	// no prescaler

	// OCR2A – Output Compare Register A
	OCR1AH = 0x01;		// interrupt after 372 cycles
	OCR1AL = 0x74;

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

// configuration of pin change interrupt
void config_rx_int(void){
	PCMSK1 |= (1 << PCINT14);
}

// enable pin change interrupt
void enable_rx_int(void){
	PCICR |= (1 << PCIE1);
}

// disable pin change interrupt
void disable_rx_int(void){
	PCICR &= ~(1 << PCIE1);
}

// configuration of Output Compare Match A Interrupt
void config_interrupt_oc(void){
	//TCCR2B – Timer/Counter Control Register B
	TCCR2B |= (1 << CS20);	// no prescaler

	// OCR2A – Output Compare Register A
	OCR2A = 124;// This value needs to adjusted based on the sampling interval.starting value 124

	//	CTC: Clear Timer on Compare Match
	TCCR2A |= (1 << WGM01);
}

// enable timer 2 (Output Compare Match A)
void enable_TIMER2(void){
	TIMSK2 |= (1 << OCIE2A);
}
// disable timer 2 (Output Compare Match A)
void disable_TIMER2(void){
	//PORTA ^= (1 << PINA7);
	TIMSK2 &= ~(1 << OCIE2A);
}
// reseting timer 2 by setting timer/count register to 0
void reset_TIMER2(void){
	TCNT2 = 0x00;
}

