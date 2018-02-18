/*
 * blink_led.c
 *
 *  Created on: Nov 3, 2017
 *      Author: yadu
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "communication.h"
#include "timer.h"
#include "uart_debug.h"

int main(void)
{
	//set_TX();
	// Configure pin 7 on port A as output
	DDRA |= (1 << PINA7); // Debug-LED
#ifdef debug
	USARTInit(51);
#endif
	//DDRB |= (1 << PINB4); // Debug-LED
	setup_etu();
	sei();
	PORTA |= (1 << PINA7); // Debug-LED
	//enable_etu_TIMER1();
	// Infinite loop
	while(1)
	{
		atr();
		//while(interrupt_counter);
		//_delay_us(11*77);
//		if(counter%10 == 0)
//			_delay_us(77*12);
//		counter++;
//		PORTB ^= (1 << PINB6);
		//interrupt_counter = 1;
	}
}

// Output Compare Interrupt, used for synchronization and transmitting bits
ISR (TIMER1_COMPA_vect)
{
	if(tx_request)
	{
		if(tx_bit)
			PORTB |= (1 << PINB6);
		else
			PORTB &= ~(1 << PINB6);
	}
	tx_request = 0;
	gt_counter++;
	//USARTWriteChar(interrupt_counter & 0xff);
}
