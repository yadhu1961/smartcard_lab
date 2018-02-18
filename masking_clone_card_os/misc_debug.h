/*
 * misc_debug.h
 *
 *  Created on: Nov 29, 2017
 *      Author: ga83jeb
 */

#ifndef MISC_DEBUG_H_
#define MISC_DEBUG_H_

#include <avr/io.h>

static void aes_trigger_init(void)
{

	DDRB |= (1 << PINB4);
}

static void aes_trigger_high(void)
{

	PORTB |= (1 << PINB4);
}

static void aes_trigger_low(void)
{

	PORTB &= ~(1 << PINB4);
}

static void debug_led_init(void)
{
	DDRA |= (1 << PINA7);  // Debug-LED
}

static void debug_led_on(void)
{
	PORTA |= (1 << PINA7); // Debug-LED
}

static void debug_led_off(void)
{
	PORTA &= ~(1 << PINA7); // Debug-LED
}

static void debug_led_toggle(void)
{
	PORTA ^= (1 << PINA7); // Debug-LED
}

static void debug_pin_init(void)
{
	DDRB |= (1 << PINB5);  //DEBUG pin
}

static void debug_pin_high(void)
{
	PORTB |= (1 << PINB5);  //DEBUG pin
}

static void debug_pin_low(void)
{
	PORTB &= ~(1 << PINB5);  //DEBUG pin
}

static void debug_pin_toggle(void)
{
	PORTB ^= (1 << PINB5);  //DEBUG pin
}

#endif /* MISC_DEBUG_H_ */
