#define F_CPU 8000000UL
#define __AVR_ATmega32__
#define WAIT_TIME 200u
#define SNAKE_LENGTH 2u

#include <stdbool.h>

#include <util/delay.h>
#include <avr/io.h>

void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; i++)
        _delay_ms(1);
}

int main(void)
{
    DDRD = 0xFF;

    const uint8_t start_state = ~(0xff << SNAKE_LENGTH);
    PORTD = start_state;

    while (true)
    {
        for (int i = 0; i < 8 - SNAKE_LENGTH; ++i)
        {
            delay_ms(WAIT_TIME);
            PORTD <<= 1;
        }

        for (int i = 0; i < 8 - SNAKE_LENGTH; ++i)
        {
            delay_ms(WAIT_TIME);
            PORTD >>= 1;
        }
    }
}
