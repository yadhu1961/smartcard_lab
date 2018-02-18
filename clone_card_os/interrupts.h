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


void config_rx_int(void);
void enable_rx_int(void);
void disable_rx_int(void);

void enable_TIMER2(void);
void disable_TIMER2(void);
void reset_TIMER2(void);


void config_interrupt_oc(void);

#endif /* TIMER_H_ */
