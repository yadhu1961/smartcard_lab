/*
 * pin_change_int.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t prev_state = 0;
volatile uint8_t present_state = 0;

int main()
{
	DDRA |= (1 << PINA7); // Debug-LED
	PORTA |= (1 << PINA7); // Debug-LED
	DDRB &= ~( 1 << PINB6 );
	PCMSK1 |= (1 << PCINT14);
	PCICR |= (1 << PCIE1);

	sei();
	while(1);
}


// Pin Change Interrupt, used for receiving.
ISR (PCINT1_vect)
{
	present_state = (PINB & (1 << PINB6)); // Debug-LED
	// detecting falling edge
	//if(present_state != prev_state){

		//Toggle led when interrupt happens
		PORTA ^= (1 << PINA7); // Debug-LED
	//}
	prev_state = present_state;
}


