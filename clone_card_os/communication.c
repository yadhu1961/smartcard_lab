/*
 * communication.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */


//TODO Still have to implement error handling mechanism.
#include "communication.h"

volatile uint8_t tx_bit = 1;
volatile uint8_t tx_request = 0;
volatile uint8_t gt_counter = 4;
volatile uint8_t sample_counter = 0;
volatile uint8_t rx_active = 1,rx_done=0;;
volatile uint8_t samples[3] = {0};
volatile uint8_t bits_count = 0;

uint8_t key[16] = {0};
uint8_t *ptr;

static uint8_t * byte_2_array(uint8_t byte, uint8_t *byte_array)
{
	int i;
	byte_array[0] = 0;//start bit
	// bit shifting
	for(i=1;i<9;i++)
		byte_array[i] = (byte >> (i-1)) & 1;
	// calculate parity bit from (AVR-lib)
	byte_array[9] = parity_even_bit(byte);
	byte_array[10] = 1; //stop  bit
	return byte_array;
}

//Enabling transmission mode, Indicating card is going to transmit the data.
static void set_TX(void)
{
	PORTB |= (1 << PINB6);
	DDRB |= (1 << PINB6);
}

//Pulling line low indicating that card is in wait state.
void set_RX (void)
{
	DDRB &= ~( 1 << PINB6 );
}

//Sends answer to reset sequence
void atr()
{
	send_byte(0x3b);
	send_byte(0x90);
	send_byte(0x11);
	send_byte(0x00);
}

void send_byte(uint8_t byte)
{
	uint8_t array[11];
	uint8_t counter = 0;

	//Change to TX mode starts
	disable_rx_int();
	enable_etu_TIMER1();
	set_TX();
	//Change to TX modes ends hier

	//while(gt_counter < 3); //This is to maintain the guard time.
	byte_2_array(byte,array);
	for(counter = 0;counter<11;counter++)
		send_bit(array[counter]);
	//gt_counter = 0;

	//Configuring again for receiving
	disable_etu_TIMER1();
	//Here Have to enable rx mode,since tx is completed.
	set_RX();
	//Very important to give delay between changing direction and enabling interrupt.
	//Otherwise observed unwanted behavior in pin.
	_delay_us(20);
	//Enabling pin change interrupt.
	enable_rx_int();
}

void send_bit(uint8_t bit)
{
	tx_bit = bit;
	tx_request = 1;
	//Wait until one etu elapses.
	//I am trying to optimally utilize this time, By reading the seed bit from adc
	//Not sure whether it works, But try it. read a bit of adc value here.
	//Hoping it will take less than 77.7 microseconds.
	while(tx_request);
}

void receive_aes_key()
{
	for(uint8_t i = 0; i<16;i++)
	{
		key[i] =  receive_byte();
	}
}

int8_t receive_command()
{
	uint8_t command_byte;
	receive_byte();
	command_byte = receive_byte();
	receive_byte();
	receive_byte();
	receive_byte();
	return command_byte;
}

void send_decypted_key()
{
	for(uint8_t i = 0; i<16;i++)
	{
		send_byte(key[i]);
	}
	//memset(key,0,16);
}

#if STACK_MEASURE
uint16_t StackCount(void)
{
	const uint8_t *p = &__stack;
	uint16_t       c = 0;

	//p = &_end;

	while(*p != STACK_CANARY)
	{
		p--;
		c++;
	}

	return (c);
}
#endif

void t0()
{
	//Minimum time observed between consecutive transactions.
	//is 3.8 milliseconds, Looks like PC script does speed adjustment based on video speed.
	uint8_t command_byte = 0;
	//All logic to configure the card as receiver and enabling pin change interrupt goes here.
	atr();
	while(1)
	{

#if SHUFFLING || DUMMY || MASKING
		disable_adc_int();
#endif
		command_byte = receive_command();
		//aes_trigger_low();
		send_byte(command_byte);
		receive_aes_key();
		send_byte(0x61);
		send_byte(0x10);

		command_byte = receive_command();
		send_byte(command_byte);
		//Some where before this stage prepare the seed for PRNG.
		//One strategy might be to read one byte in every etu, then
		//Finally combine when we are doing decryption to create prng's
		//Since complete generation of a TRNG is difficult in one etu.
		//debug_pin_high();
		//Here I will have to do aes decryption with master key.
		aes_trigger_high();
		aes_decrypt(key);
		aes_trigger_low();
		//debug_pin_low();
#if SHUFFLING || DUMMY || MASKING
		enable_adc_int();
#endif

		send_decypted_key();
		aes_trigger_low();
		send_byte(0x90);
#if STACK_MEASURE
		uint16_t temp = StackCount();
		//send_byte(temp<<8);
		send_byte(temp & 0xff);
#else
		send_byte(0x00);
#endif

	}
}

uint8_t receive_byte()
{
	uint8_t byte = 0;
	uint8_t bit = 0;
	while(1)
	{
		while(rx_active)
		{
			if(rx_done)
			{
				rx_done = 0;
				if(sample_counter == 3)
				{
					bit = ((samples[0]+samples[1]+samples[2]) > 1);
					if(bits_count < 8)
						byte |= bit << bits_count;
					bits_count++;
					sample_counter = 0;
					if(bits_count == 9)
					{
						disable_TIMER2();
						rx_active = 0;
						//TODO I have to do parity validation,
						enable_rx_int();
						break;
					}
				}
				samples[sample_counter] = (PINB & (1 << PINB6));
				sample_counter++;
			}
		}
		//Another break in here. to exit from receive_byte method, once the complete byte is received
		if(bits_count == 9)
		{
			bits_count = 0;
			break;
		}
	}
	return byte;
}
