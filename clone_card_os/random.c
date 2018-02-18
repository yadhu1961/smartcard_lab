/*
 * random.c
 *
 *  Created on: Jan 4, 2018
 *      Author: Pramod Tikare Muralidhara
 */

#include "random.h"
#if (SHUFFLING || DUMMY || MASKING)

//#include "uart_debug.h"

//This global variable stores the generated seed in init_random
uint8_t seed;

// Primitive polynomial x^8+x^6+x^5+x^4+x^0 => 101110001
// Polynomial mask omit the last bit => 10111000
// Refer https://www.maximintegrated.com/en/app-notes/index.mvp/id/4400
#define POLYMASK8 0xB8

inline uint8_t rand_lfsr()
{
	//Added for debugging purpose.
	//debug_led_toggle();
	// provided seed is the starting state for the LFSR

	uint8_t lsb = seed & 1;   /* Get LSB (i.e., the output bit). */
	seed >>= 1;                /* Shift register */
	if (lsb)
		seed ^= POLYMASK8;		/* If the output bit is 1, add the mask. */
	return seed;
}

// 4 * 2LSBs
//void generate_seed_2()
//{
//	uint8_t adc_val0,adc_val1,adc_val2,adc_val3;
//	while(1)
//	{
//		// Read last 2 LSBs for 4 conversion
//		// 4*2LSBs
//		adc_val0 = (get_val_ADC() & 0x03);
//		adc_val1 = (get_val_ADC() & 0x03);
//		adc_val2 = (get_val_ADC() & 0x03);
//		adc_val3 = (get_val_ADC() & 0x03);
//		seed = (adc_val3) | (adc_val2 << 2) | (adc_val1 << 4) | (adc_val0 << 6);
//		if(!(seed==0xFF))
//			break;
//	}
//}

// 8 * 1LSB
//void generate_seed_1()
//{
//	//Added for debugging remove later.
//	debug_led_toggle();
//	uint8_t adc_val[8];
//	while(1)
//	{
//		for(uint8_t i = 0; i < 7; i++)
//		{
//			//get_val_ADC returns 8 LSBs of the conversion
//			adc_val[i] = (get_val_ADC() & 0x01);
//		}
//		seed = (adc_val[7]) | (adc_val[6] << 1) | (adc_val[5] << 2) | (adc_val[4] << 3) |
//				(adc_val[3] << 4) | (adc_val[2] << 5) | (adc_val[1] << 6) | (adc_val[0] << 7);
//		if(!(seed==0xFF))
//			break;
//	}
//}
// Von Neumann Corrector. 01 => 1, 10 => 0
//void generate_seed_1_VNC()
//{
//	uint8_t adc_val;
//	uint8_t seed_bits[8];
//	uint8_t i = 0;
//	while(1)
//	{
//		while(i<8)
//		{
//			adc_val = (get_val_ADC() & 0x03);
//
//			if(adc_val == 1)
//			{
//				seed_bits[i] = 1;
//				i++;
//			}
//			else if (adc_val == 0)
//			{
//				seed_bits[i] = 0;
//				i++;
//			}
//		}
//		seed = (seed_bits[7]) | (seed_bits[6] << 1) | (seed_bits[5] << 2) | (seed_bits[4] << 3) |
//				(seed_bits[3] << 4) | (seed_bits[2] << 5) | (seed_bits[1] << 6) | (seed_bits[0] << 7);
//		if(!(seed==0xFF))
//		{
//			//USARTWriteChar(seed);
//			break;
//		}
//	}
//}

/**
 * Check whether it is possible to read a value here,
 * within one etu., If so do this always, fill the byte
 * This will be finally used as PRNG seed.
 */
//void read_seed_bit()
//{
//	uint8_t temp;
//	temp = get_val_ADC() & 0x01;
//	//Combining the newly read bit to seed.
//	seed = (seed << 1) + temp;
//}
#endif
