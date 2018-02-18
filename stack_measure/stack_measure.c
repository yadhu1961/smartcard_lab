#include <avr/io.h>
#include <util/delay.h>
#include "uart_debug.h"

#define STACK_CANARY 0xc5

extern uint8_t _end;
extern uint8_t __stack;

void StackPaint(void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void StackPaint(void)
{
//#if 0
    uint8_t *p = &_end;

    while(p <= &__stack)
    {
        *p = STACK_CANARY;
        p++;
    }
//#else
//    __asm volatile ("    ldi r30,lo8(_end)\n"
//                    "    ldi r31,hi8(_end)\n"
//                    "    ldi r24,lo8(0xc5)\n" /* STACK_CANARY = 0xc5 */
//                    "    ldi r25,hi8(__stack)\n"
//                    "    rjmp .cmp\n"
//                    ".loop:\n"
//                    "    st Z+,r24\n"
//                    ".cmp:\n"
//                    "    cpi r30,lo8(__stack)\n"
//                    "    cpc r31,r25\n"
//                    "    brlo .loop\n"
//                    "    breq .loop"::);
//#endif
}


uint16_t StackCount(void)
{
	const uint8_t *p = &_end;
	uint16_t       c = 0;

	while(*p == STACK_CANARY && p <= &__stack)
	{
		p++;
		c++;
	}

	return c;
}

long int multiplyNumbers(int n)
{
    if (n >= 1)
        return n*multiplyNumbers(n-1);
    else
        return 1;
}

/*Make sure to disable the optimization, otherwise difficult to measure the stack usage
 *
 */

int main()
{
	DDRA |= (1 << PINA7);
	USARTInit(15);
	uint16_t count1 = 0,count2 = 0;
	count1 = StackCount();
	multiplyNumbers(5);
	count2 = StackCount();
	int used_stack = count1 - count2;
	while(1)
	{
		//USARTWriteChar(StackCount());
		serial_printf(&used_stack,2);
		//serial_printf(&count2,2);
		//serial_printf(&factorial,4);
		if(used_stack > 0)
			PORTA ^= (1 << PINA7);
		_delay_ms(1000);
	}
	//return factorial;
}
