/*
 * communication.h
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */

#define STACK_MEASURE 0

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/parity.h>
//#include <string.h>
//#include "uart_debug.h"
#include "interrupts.h"
#include "misc_debug.h"
#include "aes.h"


#define STACK_CANARY 0xc5
extern uint8_t _end;
extern uint8_t __stack;

#if SHUFFLING || DUMMY || MASKING
#include "adc.h"
#endif

//Global variables used across files.
extern volatile uint8_t tx_bit;
extern volatile uint8_t tx_request;
extern volatile uint8_t gt_counter;
extern volatile uint8_t sample_counter;
extern volatile uint8_t rx_active,rx_done;
//extern volatile uint8_t bit_array[10];
extern volatile uint8_t samples[3];
extern volatile uint8_t bit;
extern volatile uint8_t bits_count;

void atr();
void send_bit(uint8_t);
void send_byte(uint8_t);
uint8_t bitarray_2_byte();
void t0();
uint8_t receive_byte();


#endif /* COMMUNICATION_H_ */
