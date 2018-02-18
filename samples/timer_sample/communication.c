/*
 * communication.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */
#include "communication.h"

volatile uint16_t tx_request = 0,gt_counter = 0;
volatile uint8_t tx_bit = 1;

static uint8_t * byte_2_array(uint8_t byte, uint8_t *byte_array)
{
	int i;
	byte_array[0] = 0;// first bit is always 0
	// bit shifting
	for(i=1;i<9;i++)
		byte_array[i] = (byte >> (i-1)) & 1;
	// calculate parity bit (AVR-lib)
	byte_array[9] = parity_even_bit(byte);
	byte_array[10] = 1; //stop  bit
	return byte_array;
}

/////////////////////////////////////////////////////////////////
static void set_TX(void)
{
	PORTB |= (1 << PINB6);		// mandatory apparently
	DDRB |= (1 << PINB6);
}

void atr()
{
	send_byte(0x3b);
	PORTA ^= (1 << PINA7);
	send_byte(0x90);
	PORTA ^= (1 << PINA7);
	send_byte(0x11);
	PORTA ^= (1 << PINA7);
	send_byte(0x00);
	PORTA ^= (1 << PINA7);
}

void send_byte(uint8_t byte)
{
	uint8_t array[11];
	uint8_t counter = 0;
	set_TX();
	enable_etu_TIMER1();
	while(gt_counter < 11); //This is to maintain the guard time.
	byte_2_array(byte,array);
	for(counter = 0;counter<11;counter++)
		send_bit(array[counter]);
	gt_counter = 0;
	disable_etu_TIMER1();
	//Here Have to enable rx mode,since tx is completed.

}

void send_bit(uint8_t bit)
{
	tx_bit = bit;
	tx_request = 1;
	while(tx_request);
}

