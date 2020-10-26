// Krzysztof Ragan 249026
// Kinga Długosz 249002

#define _AVR_ATmega32_
#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>

void delay_ms(int ms)
{
	volatile long unsigned int i;
	for (i = 0; i < ms; i++)
		_delay_ms(1);
}

void delay_us(int us)
{
	volatile long unsigned int i;
	for (i = 0; i < us; i++)
		_delay_us(1);
}


#define RS 0
#define RW 1
#define E 2

void LCD2x20_init(void)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = 0x38; 
	PORTC &= ~(1 << E);
	_delay_us(120);

	PORTC |= (1 << E);
	PORTD = 0x0e; 
	PORTC &= ~(1 << E);
	_delay_us(120);

	PORTC |= (1 << E);
	PORTD = 0x06;
	PORTC &= ~(1 << E);
	_delay_us(120);
}

void LCD2x20_clear(void)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = 0x01;
	PORTC &= ~(1 << E);
	delay_ms(120);
}

void LCD2x20_putchar(int data)
{
	PORTC |= (1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = data;
	PORTC &= ~(1 << E);
	_delay_us(120);
}

void LCD2x20_pos(int wiersz, int kolumna)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	delay_ms(1);
	PORTD = 0x80 + (wiersz - 1) * 0x40 + (kolumna - 1);
	delay_ms(1);
	PORTC &= ~(1 << E);
	_delay_us(120);
}

// Set point (w %)
int _sp = 40;
// Histereza (w %)
int _h = 10;
// Error 
int _e;
// Error jako decimal
int dec_e;
// process value (zakres 0-1000)
float _pv;
// process value jako int
int int_pv;
// process value jako decimal
int dec_pv;

int main(void)
{
	char tmp[16];

	int i;

	DDRD = 0xff;
	PORTD = 0x00;
	DDRC = 0xff;
	PORTC = 0x00;
	DDRB = 0x00;
	PORTB = 0xff;

	_delay_ms(500);

	LCD2x20_init();
	LCD2x20_clear();

	ADMUX = 0x40;
	ADCSRA = 0xe0;

	while (1)
	{
		// Konwersja ADC poprzez ustawienie ADSC 
		ADCSRA = ADCSRA | (1 << ADSC);

		while (ADCSRA & (1 << ADSC))
			;

		_pv = ADC;
		int_pv = (_pv / 1000) * 100;
		_e = _sp - int_pv;
		dec_pv = (((_pv / 1000) * 100) - int_pv) * 10;
		dec_e = (10 - dec_pv) % 10;

		// ON
		if (_e > (_h / 2))
		{
			PORTC = ~(0x01 << 5);
		}

		// OFF
		if (_e < -(_h / 2))
		{
			PORTC = (0x01 << 5);
		}

		if (!(PINB & (8 << PB0)))
		{
			_sp = 50;
		}
		if (!(PINB & (4 << PB0)))
		{
			_sp = 40;
		}
		if (!(PINB & (2 << PB0)))
		{
			_h = 10;
		}
		if (!(PINB & (1 << PB0)))
		{
			_h = 12;
		}

		LCD2x20_pos(1, 1);
		sprintf(tmp, "SP=%2d PV=%3d.%1d%% ", _sp, int_pv, dec_pv);
		for (i = 0; i < 20; i++)
		{
			LCD2x20_putchar(tmp[i]);
		}

		LCD2x20_pos(2, 1);
		sprintf(tmp, "H=%2d   E=%3d.%1d%%  ", _h, _e, dec_e);
		for (i = 0; i < 20; i++)
		{
			LCD2x20_putchar(tmp[i]);
		}
		delay_ms(500);
	}

	return 0;
}