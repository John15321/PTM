#define F_CPU 8000000UL
#define __AVR_ATmega32__

#include <stdbool.h>

#include <util/delay.h>
#include <avr/io.h>

#ifndef set_pin_to_high
/*
* Sets value on a given pin to High
*/
#define set_pin_to_high(port, pin) port |= (1 << pin)
#endif

#ifndef set_pin_to_low
/*
* Sets value on a given pin  to Low
*/
#define set_pin_to_low(port, pin) port &= ~(1 << pin)
#endif

#ifndef toggle_pin_state
/*
* Toggles output value on a given pin
*/
#define toggle_pin_state(port, pin) port ^= (1 << pin)
#endif

/*
* Delay in miliseconds
*/
void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; i++)
    {
        _delay_ms(1);
    }
}

/*
* Represents three states of the LED. Is either blinking
* (STATE_BLINKING), is turned off (STATE_OFF), or is turned on (STATE_ON)
*/
enum State
{
    STATE_BLINKING,
    STATE_OFF,
    STATE_ON
};

/*
* Reads value from a button, on a given pin, defined in PIN_BUTTON
*/
bool read_button()
{
    return PINB & PIN_BUTTON;
}

int main(void)
{
}
