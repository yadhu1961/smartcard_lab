/*
 * uart_debug.c
 *
 *  Created on: Nov 18, 2017
 *      Author: yadu
 */

#include "uart_debug.h"

#ifdef debug
//This fuction writes the given "data" to
//the USART which then transmit it via TX line
void USARTWriteChar(char data){

   //Wait untill the transmitter is ready
   while(!(UCSR0A & (1<<UDRE0))){
      //Do nothing
   }

   //Now write the data to USART buffer
   UDR0=data;
}

//This function is used to initialize the USART
//at a given UBRR value
void USARTInit(uint16_t ubrr_value){

   //Set Baud rate
   UBRR0L = ubrr_value;
   UBRR0H = (ubrr_value>>8);

   /*Set Frame Format
   >> Asynchronous mode
   >> No Parity
   >> 1 StopBit
   >> char size 8
   */
   UCSR0C = (3<<UCSZ00); // Asynchronous 8 N 1

   //Enable The receiver and transmitter
   UCSR0B=(1<<RXEN0)|(1<<TXEN0);
}


void serial_printf(uint8_t *data,int len)
{
	int count = 0;
	for(count= 0; count<len;count++)
		USARTWriteChar(data[count]);
}
#endif

