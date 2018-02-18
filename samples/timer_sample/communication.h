/*
 * communication.h
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/parity.h>
#include "timer.h"

extern volatile uint16_t tx_request,gt_counter;
extern volatile uint8_t tx_bit;


void atr();
void send_bit(uint8_t);
void send_byte(uint8_t);


#endif /* COMMUNICATION_H_ */
