#define __AVR_ATmega32__
#define F_CPU 8000000UL


#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#define LED 6
#define BUTTON 0

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


#ifndef pin_state
/*
* Returns pin state, as either 0 or a non 0 integer
* 0 if the pin is low, and non-0 if the pin is high
*/
#define pin_state(port, pin) port & (1 << pin)
#endif


int main()
{
    // Set all pins of the PORTD as output
    DDRD = 0xFF;
    // Set Pin B0 as input
    set_pin_to_low(DDRB, BUTTON);
    // DDRB &= ~(1 << BUTTON); 
    // set_pin_to_low(PORTB, BUTTON);
    set_pin_to_high(PORTD, LED);
    while (1)
    {

        if (!(pin_state(PORTB, BUTTON)))
        {
            set_pin_to_low(PORTD, LED);
        }
        else
        {
            set_pin_to_high(PORTD, LED);
        }
        
        
    }
    return 0;
}