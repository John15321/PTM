/**************************************/
/*              ARE 2008              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

// Jan Bronicki 249011
// Borys Staszczak 248958

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

void LCD2x16_init(void)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = 0x38; // dwie linie, 5x7 punktow
	PORTC &= ~(1 << E);
	_delay_us(120);

	PORTC |= (1 << E);
	PORTD = 0x0e; // wlacz wyswietlacz, kursor, miganie
	PORTC &= ~(1 << E);
	_delay_us(120);

	PORTC |= (1 << E);
	PORTD = 0x06;
	PORTC &= ~(1 << E);
	_delay_us(120);
}

void LCD2x16_clear(void)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = 0x01;
	PORTC &= ~(1 << E);
	delay_ms(120);
}

void LCD2x16_putchar(int data)
{
	PORTC |= (1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	PORTD = data;
	PORTC &= ~(1 << E);
	_delay_us(120);
}

void LCD2x16_pos(int wiersz, int kolumna)
{
	PORTC &= ~(1 << RS);
	PORTC &= ~(1 << RW);

	PORTC |= (1 << E);
	delay_ms(1);
	PORTD = 0x80 + (wiersz - 1) * 0x40 + (kolumna - 1);
	PORTC &= ~(1 << E);
	_delay_us(120);
}

// Set point (in 0.1%)
int _sp = 600;
// Error value
int _e;
// Integer part of the error
int int_e;
// Decimal value of the error
int dec_e;
// Whole process value (in 0-1023 range)
float process_value;
// Process value with decimal part
int _pv;
// Integer part of process value
int _ipv;
// Decimal part of process value
int _decpv;
// Control value
int _cv = 0;

int _xp = 200;
int _T = 2000;
int iter = 0;

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

	_delay_ms(200);

	LCD2x16_init();
	LCD2x16_clear();

	ADMUX = 0x40;
	ADCSRA = 0xe0;

	while (1)
	{
		// Start an ADC conversion by setting ADSC bit (bit 6)
		ADCSRA = ADCSRA | (1 << ADSC);

		// Wait until the ADSC bit has been cleared
		while (ADCSRA & (1 << ADSC))
			;

		process_value = ADC;
		_pv = (process_value / 1023.0) * 1000;
		_ipv = _pv / 10;
		_decpv = _pv % 10;

		// Jan Bronicki 249011
		// Borys Staszczak 248958

		_e = _sp - _pv;
		int_e = _e / 10;
		dec_e = _e % 10;

		if (_e < -_xp / 2)
		{
			_cv = 0;
		}
		else if (_e > _xp / 2)
		{
			_cv = 100;
		}
		else
		{
			_cv = (((_e + _xp / 2) * 20 / _xp)) * 5;
		}

		//dioda

		if (iter < _T / 200 * _cv / 100)
		{
			PORTC &= ~(1 << PC3);
		}
		else
		{
			PORTC |= (1 << PC3);
		}

		if (!(PINB & (1 << PB0)))
		{
			_sp = 500;
		}

		if (!(PINB & (2 << PB0)))
		{
			_sp = 400;
		}

		if (!(PINB & (4 << PB0)))
		{
			_xp = 300;
		}

		if (!(PINB & (8 << PB0)))
		{
			_xp = 400;
		}

		LCD2x16_pos(1, 1);
		sprintf(tmp, "SP=%2d%% PV=%3d.%1d%%", _sp / 10, _ipv, abs(_decpv));
		for (i = 0; i < 16; i++)
		{
			LCD2x16_putchar(tmp[i]);
		}

		LCD2x16_pos(2, 1);
		sprintf(tmp, "Xp=%2d%%   E=%3d.%1d%%", _xp/10, int_e, abs(dec_e));
		for (i = 0; i < 16; i++)
		{
			LCD2x16_putchar(tmp[i]);
		}
		delay_ms(500);

		iter++;
		if (iter >= _T / 200)
			iter = 0;
	}

	return 0;
}