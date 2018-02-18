/*
 * adc.h
 *
 *  Created on: Jan 04, 2018
 *      Author: Pramod Tikare Muralidhara
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "aes.h"
//#include "misc_debug.h"

extern uint8_t seed;

void adc_init(void);
uint8_t get_val_ADC(void);

inline void disable_adc_int()
{
    ADCSRA &= ~(1 << ADIE);
}

inline void enable_adc_int()
{
    ADCSRA |= (1 << ADIE);
}

#endif
