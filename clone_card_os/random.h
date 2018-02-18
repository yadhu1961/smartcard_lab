/*
 * random.h
 *
 *  Created on: Jan 4, 2018
 *      Author: Pramod Tikare Muralidhara
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <avr/io.h>
//#include "misc_debug.h"
#include "adc.h"

extern uint8_t seed;

uint8_t rand_lfsr();

#endif /* RANDOM_H_ */
