/*
 * aes.h
 *
 *  Created on: Nov 29, 2017
 *      Author: pramod
 */

#ifndef AES_H_
#define AES_H_

//#define enable_key_expansion 1
#define MASKING
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

typedef unsigned char uint8_t;

void key_expansion(uint8_t*,uint8_t*);
void aes_decrypt(uint8_t * );

#endif /* AES_H_ */
