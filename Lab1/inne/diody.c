#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>

#define PROGRAM_DDRX DDRD

#define DIODE_PORTD_NO PD1
#define BUTTON_PORTD_NO PD6

void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; ++i)
        _delay_ms(1);
}

int main(void)
{
    DDRD = (1 << DIODE_PORTD_NO);

    while(1)
    {
        PORTD = 0x0;
        delay_ms(200);
        PORTD = (1 << DIODE_PORTD_NO);
        delay_ms(200);
    }
}