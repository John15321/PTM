#define F_CPU 8000000UL
#define __AVR_ATmega32__

#include <stdbool.h>

#include <util/delay.h>
#include <avr/io.h>

#define DDRX DDRD

// to which PINB button is connected
#define PIN_BUTTON PD5
#define PIN_DIODE PD6

void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; i++)
        _delay_ms(1);
}

enum State
{
    STATE_BLINKING,
    STATE_OFF,
    STATE_ON
};


class Button
{
public:
    void tick(bool state, unsigned long currentTime)
    {
        if (state != lastKnownState_)
        {
            lastKnownState_ = state;
            lastKnownStateChangeTime_ = currentTime;
        }

        if (state != )    
    }


private:
    bool isOn_ = false;
    bool lastKnownState_ = false;
    long unsigned lastKnownStateChangeTime_ = 0;
};

int main(void)
{
    DDRX = (1 << PIN_DIODE);  // set dioe pin to out
    DDRX = DDRX & ~(1 << PIN_BUTTON);  // set button pin to input

    int current_state = STATE_BLINKING;
    long unsigned ms_after_program_starts = 0;

    bool last_button_state = false;  // off
    long unsigned last_button_change_time = ms_after_program_starts;  // time when state changed
    
    bool button_state = false;  // off
    long unsigned ms_to_aknowledge_press = 30;  // in ms

    while (true)
    {
        switch (current_state)
        {
            case STATE_BLINKING:
                /* ... */
            case STATE_OFF:
                /* ... */
            case STATE_ON:
        }

        int current_button = read_button();

        if (current_button != last_button_state)
        {
            last_button_change_time = ms_after_program_starts;
            last_button_state = current_button;
        }

        if (button_state != current_button
            && ms_after_program_starts - last_button_change_time > ms_to_aknowledge_press)
        {
            button_state = current_butto
        }

        ms_after_program_starts += 1;
        delay_ms(1);
    }
}
// Parking dla kursorow
/*
//  //  //  //
*/
