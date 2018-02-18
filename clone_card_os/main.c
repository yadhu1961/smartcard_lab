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
#include "interrupts.h"
#include "misc_debug.h"
#include "aes.h"
//#include "uart_debug.h"
#if (SHUFFLING || DUMMY || MASKING)
#include "adc.h"
#endif

#if STACK_MEASURE
//Stack measurement part starts here
#define STACK_CANARY 0xc5
extern uint8_t _end;
extern uint8_t __stack;

void StackPaint(void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void StackPaint(void)
{
    uint8_t *p = &_end;
    while(p <= &__stack)
    {
        *p = STACK_CANARY;
        p++;
    }
}
//Stack measurement part ends here
#endif

int main(void)
{
	//debug_led_init();
	//debug_pin_init();
	aes_trigger_init();
#if (SHUFFLING || DUMMY || MASKING)
	adc_init();
#endif
	//debug_led_off();
	aes_trigger_low();
#ifdef debug
	USARTInit(15);
#endif
	//Configuring TX interrupt for 77.5 us
	setup_etu();
	//Configuring RX sampling interrupt for 25.8 us 
	config_interrupt_oc();
	//Configuring pin change interrupt for detecting the start bit.
	config_rx_int();
	sei();
	//Disable all timers
	disable_TIMER2();
	disable_etu_TIMER1();
	disable_rx_int();
	t0();
	//while(1);
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
	//Not using this anymore.
	//gt_counter++;
}

ISR (TIMER2_COMPA_vect)
{
	if(rx_active)
	{
		rx_done = 1;
	}
}

// Pin Change Interrupt, used for receiving.
ISR (PCINT1_vect)
{
	//aes_trigger_toggle();
	if(!(PINB & (1 << PINB6)))
	{
			_delay_us(56);//This value looks perfect
			enable_TIMER2();
			reset_TIMER2();
			rx_active = 1;
			disable_rx_int();				// disable pin change interrupt after start bit (must be enabled after received/transmitted byte)
	}
}
