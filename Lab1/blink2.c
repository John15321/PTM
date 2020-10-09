#define __AVR_ATmega32__
#define F_CPU 8000000

#include "avr/io.h"
#include "stdlib.h"
#include "string.h"
#include "util/delay.h"
#ifndef _BV
#define _BV(bit)                (1<<(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)        reg |= (_BV(bit))
#endif

#ifndef cbi
#define cbi(reg,bit)        reg &= ~(_BV(bit))
#endif

int main() {
    DDRD = 0xFF;
    PORTD = 0xFF;

    uint8_t tab[] = {3, 6, 12, 24, 48, 96, 192, 96, 48, 24, 12, 6};
    while (1) {

        for(uint8_t i = 0; i < 12; i++){
            PORTD = tab[i];
            _delay_ms(500);
        }
    }
}