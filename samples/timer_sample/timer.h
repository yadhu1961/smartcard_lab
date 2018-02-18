/*
 * timer.h
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void enable_etu_TIMER1(void);
void setup_etu(void);
void disable_etu_TIMER1(void);



#endif /* TIMER_H_ */
