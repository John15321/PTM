#define __AVR_ATmega32__
#define F_CPU 8000000UL

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#include "pin_manipulation.h"

#define LED 6
#define BUTTON 0

void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; i++)
        _delay_ms(1);
}

void options(uint8_t opt)
{
    //opcja pierwsza co sekunde dioda zmienia swoj stan
    if (opt == 1)
    {
        toggle_pin_state(PORTD, LED);
        _delay_ms(1000);
    }
    else if (opt == 2) //opcja druga dioda ciagle swieci
    {
        set_pin_to_high(PORTD, LED);
    }
    else if (opt == 3) //opcja trzecia dioda zgaszona
    {
        set_pin_to_low(PORTD, LED);
    }
}

int main()
{
    uint8_t opt = 1;

    // Set all pins of the PORTD as output
    DDRD = 0xFF;

    // Set Pin B0 as input
    set_pin_to_low(DDRB, BUTTON);
    pullup_high(PORTB, BUTTON);

    // Make sure LED is high
    set_pin_to_high(PORTD, LED);

    while (1)
    {
        //sprawdzanie czy przycisk jest wcisniety
        if (bit_is_clear(PINB, BUTTON))
        {
            //zmiekszenie wartosci opt o
            opt++;
            //jesli opt jest wieksze niz 3 ustaw wartosc na 1
            if (opt > 3)
                opt = 1;
        }
        //jesli przycisk jest wciaz wcisniety wywoluje sie poprzednia opcja diody
        while (bit_is_clear(PINB, BUTTON))
        {
            if (opt == 1)
                options(3);
            else
                options(opt - 1);
        }
        //wywolanie opcji nr opt
        options(opt);
    }
    return 0;
}