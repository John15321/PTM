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
	delay_ms(1);
	PORTC &= ~(1 << E);
	_delay_us(120);
}

int _sp = 40;
int _xp = 30;
int _e;
int int_e;
int dec_e;
float _pv;
int full_pv;
int int_pv;
int dec_pv;
int _T = 20;
int _cv = 0;

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
	DDRC = (1 << 3) | (1 << 4);
	_delay_ms(500);

	LCD2x16_init();
	LCD2x16_clear();

	ADMUX = 0x40;
	ADCSRA = 0xe0;

	while (1)
	{
		ADCSRA = ADCSRA | (1 << ADSC);
		while (ADCSRA & (1 << ADSC))
			;
		_pv = ADC;
		full_pv = (_pv / 1023.0) * 1000;
		int_pv = full_pv / 10;
		dec_pv = full_pv % 10;
		// _e = (_sp * 10) - full_pv;
		_e = _sp - int_pv;
		int_e = _e / 10;
		dec_e = _e % 10;

		if (_e < -_xp / 2)
			_cv = 0;
		else if (_e >= _xp / 2)
			_cv = 20;
		else
			_cv = (((_e + _xp / 2) * 19 / _xp) + 1);

		for (i = 0; i < 20; i++)
		{
			if (i < _cv && _cv != 0)
			{
				PORTC |= 1 << PINC3; //wlacz diode
			}
			else
			{
				PORTC &= ~(1 << PINC3); //wylacz diode
			}
			delay_ms(10);
		}

		//przyciski
		if (!(PINB & (1 << PB0)))
		{
			_sp = 50;
			delay_ms(100);
		}
		if (!(PINB & (2 << PB0)))
		{
			_sp = 40;
			delay_ms(100);
		}
		if (!(PINB & (3 << PB0)))
		{
			_xp = 30;
			delay_ms(100);
		}
		if (!(PINB & (4 << PB0)))
		{
			_xp = 40;
			delay_ms(100);
		}

		LCD2x16_pos(1, 1);
		sprintf(tmp, "SP=%2d%% PV=%2d.%1d%% ", _sp, int_pv, dec_pv);
		for (i = 0; i < 16; i++)
		{
			LCD2x16_putchar(tmp[i]);
		}

		LCD2x16_pos(2, 1);
		sprintf(tmp, "XP=%2d%% E=%3d.%1d%%  ", _xp, _e, dec_e);
		for (i = 0; i < 16; i++)
		{
			LCD2x16_putchar(tmp[i]);
		}
		delay_ms(300);
	}

	return 0;
}
