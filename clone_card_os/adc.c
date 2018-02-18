/*
 * adc.c
 *
 *  Created on: Jan 04, 2018
 *      Author: Pramod Tikare Muralidhara
 */

#include "adc.h"

#if (SHUFFLING || DUMMY || MASKING)


void adc_init()
{

	DIDR0 = 0xFF;
	ADMUX |= 0x0A;	// 0x0A selects ADC0 and ADC0 for +ve and -ve differential inputs
	// 200x differential gain
	//ADMUX |= 0x07;		// 0x07 selects single ended pin ADC7
	//ADMUX |= (1 << ADLAR);// Consider upper 8 bits
	//ADC Enable, Auto trigger enable, highest prescalar

	// Free running mode
	ADCSRB = 0x00;

	//Why highest division factor, Faster conversion and optimal AES implementation?
	//We should have lowest division factor. As tradeoff between speed and randomness
	//Use a division factor of 8, Suits our requirements well.
	ADCSRA |= (1 << ADATE) | (1 <<  ADEN)| (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// prescaler 4.8 MHz/128 = 37.5 kHz ADC frequency
	ADCSRA |= (1 << ADSC) ;
}

//uint8_t get_val_ADC()
//{
//	uint8_t L_adc, H_adc;
//	//ADCSRA = 0xC0;	//ADCEN=ADSC = 1, ADATE=ADIF=ADIE=ADPS2:0 = 0
//	while(!(ADCSRA & (1<<ADIF)));
//	ADCSRA |= ( 1 << ADIF ); // clear interrupt flag
//	// Necessary to read both ADCH and ADCL registers
//	L_adc = ADCL;
//	H_adc = ADCH;
//	return L_adc;
//}

#if Von_Neumann_Corrector
ISR (ADC_vect)
{
	//debug_led_toggle();
//	debug_pin_high();
//	debug_pin_toggle();
	uint8_t L_adc, H_adc;
	L_adc = ADCL;
	H_adc = ADCH;
	// Von Neumann Corrector
	// if LSB = 01, seed bit = 1
	// if LSB = 10, seed bit = 0,
	// ignore otherwise
	if(L_adc == 1)
		seed = ((seed << 1) | 1);
	else if(L_adc == 2)
		seed = (seed << 1);
	ADCSRA |= ( 1 << ADIF ); // clear interrupt flag
//	debug_pin_low();
}
#else
ISR (ADC_vect)
{
	//debug_led_toggle();
	uint8_t L_adc, H_adc;
	L_adc = ADCL;
	H_adc = ADCH;
	seed = ((seed << 1) | (L_adc & 0x01));
	ADCSRA |= ( 1 << ADIF ); // clear interrupt flag
}
#endif
#endif
