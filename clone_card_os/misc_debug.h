/*
 * misc_debug.h
 *
 *  Created on: Nov 29, 2017
 *      Author: ga83jeb
 */

#ifndef MISC_DEBUG_H_
#define MISC_DEBUG_H_

#include <avr/io.h>

inline void aes_trigger_init(void)
{

	DDRB |= (1 << PINB4);
}

inline void aes_trigger_high(void)
{

	PORTB |= (1 << PINB4);
}

inline void aes_trigger_toggle(void)
{

	PORTB ^= (1 << PINB4);
}

inline void aes_trigger_low(void)
{

	PORTB &= ~(1 << PINB4);
}

inline void debug_led_init(void)
{
	DDRA |= (1 << PINA7);  // Debug-LED
}

inline void debug_led_on(void)
{
	PORTA |= (1 << PINA7); // Debug-LED
}

inline void debug_led_off(void)
{
	PORTA &= ~(1 << PINA7); // Debug-LED
}

inline void debug_led_toggle(void)
{
	PORTA ^= (1 << PINA7); // Debug-LED
}

inline void debug_pin_init(void)
{
	DDRB |= (1 << PINB5);  //DEBUG pin
}

inline void debug_pin_high(void)
{
	PORTB |= (1 << PINB5);  //DEBUG pin
}

inline void debug_pin_low(void)
{
	PORTB &= ~(1 << PINB5);  //DEBUG pin
}

inline void debug_pin_toggle(void)
{
	PORTB ^= (1 << PINB5);  //DEBUG pin
}

#endif /* MISC_DEBUG_H_ */
