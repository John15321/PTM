
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
#define pin_state(port, pin) port &(1 << pin)
#endif

#ifndef pullup_high
/*
* Pulls up a high output to input
* Needs PORTD as port input
*/
#define pullup_high(port, pin) port |= (1 << pin)
#endif