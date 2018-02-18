#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configure pin 7 on port A as output
    DDRA |= (1 << PINA7); // Debug-LED

    // Infinite loop
    while(1)
    {
        // Invert the output of pin 7 on port A
        PORTA ^= (1 << PINA7);
        _delay_ms(250);
    }

}
