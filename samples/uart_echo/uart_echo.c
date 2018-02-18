#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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


//This function is used to read the available data
//from USART. This function will wait untill data is
//available.
char USARTReadChar(){
   //Wait untill a data is available

   while(!(UCSR0A & (1<<RXC0))){
      //Do nothing
   }

   //Now USART has got data from host
   //and is available is buffer
   return UDR0;
}


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

int main(){

   //Variable Declaration
   char data;

   /*First Initialize the USART with baud rate = 19200bps
   for Baud rate = 19200bps
   UBRR value = 51
   */
   USARTInit(15);    //UBRR = 51
   DDRA |= (1 << PINA7); // Debug-LED

   //Loop forever
   while(1) {

    //Read data
    //data=USARTReadChar();

    USARTWriteChar('A');
    // Invert the output of pin 7 on port A
    //if(data == 0x01)
      //PORTA ^= (1 << PINA7);
    _delay_us(100);
   }
   return(0);
}
