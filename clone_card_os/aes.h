/*
 * aes.h
 *
 *  Created on: Nov 29, 2017
 *      Author: pramod
 */
#ifndef AES_H_
#define AES_H_

/*
 * Allowed combinations
 * Shuffling + Dummy
 *
 */

#define MASKING 0
#define SHUFFLING 0
#define DUMMY 0
#define Von_Neumann_Corrector 0

#include <avr/cpufunc.h>
#include <stdlib.h>
#include <stdio.h>
//#include "misc_debug.h"
//#include "uart_debug.h"

#if SHUFFLING || DUMMY || MASKING
#include "random.h"
#endif


//#define likely(x)      __builtin_expect(!!(x), 1)
//#define unlikely(x)    __builtin_expect(!!(x), 0)

typedef unsigned char uint8_t;
#define enable_key_expansion 0

//We need declaration
//extern uint8_t cipher_key_exp[176];

//void inv_sub_bytes(uint8_t*);
//void add_round_key(uint8_t *, uint8_t);
//void inv_shift_rows(array_of_4_char *);
//void inv_mix_columns(array_of_4_char *);
//void key_expansion(uint8_t*,uint8_t*);

//void rotate(uint8_t *);
//void sbox_sub(uint8_t *);

void aes_decrypt(uint8_t * );

#endif /* AES_H_ */
