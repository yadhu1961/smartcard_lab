
//Insert following code in main.c

//Stack measurement part starts here
#define STACK_CANARY 0xc5
extern uint8_t _end;
extern uint8_t __stack;

void StackPaint(void) __attribute__ ((naked)) __attribute__ ((section (".init1")));

void StackPaint(void)
{
    uint8_t *p = &_end;
    while(p <= &__stack)
    {
        *p = STACK_CANARY;
        p++;
    }
}
//Stack measurement part ends here

Call the following function after decryption, It gives the amount of stack used.
uint16_t StackCount(void)
{
    const uint8_t *p = &__stack;
    uint16_t       c = 0;

    //p = &_end;

    while(*p != STACK_CANARY)
    {
        p--;
        c++;
    }

    return (c);
}

