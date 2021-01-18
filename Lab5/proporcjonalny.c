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

	// Set point (in 0.1%)
	int _sp = 60;
	// Error value
	int _e;
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

	int _Xp = 20;

	int T0 = 20;

	while (1)
	{
		ADMUX = 0x40;
		ADCSRA = 0xe0;
		_pv = ADC;
		process_value = (_pv / 1023)*100;
		_ipv = (int)process_value;
		_e = _sp - process_value;
		_decpv = (process_value - _ipv)*10;
		dec_e = (_e - (int)_e)*10;

		if (dec_e < 0) //zabezpieczenie przed wyświetlaniem wartości ujemnej czesci dziesietnej
		{
			dec_e = (-1);
		}

		if (_e < -_Xp / 2)
		{
			_cv = 0;
		}
		else if (_e > _Xp / 2)
		{
			_cv = 100;
		}
		else
		{
			int i = 0;
			_cv = ((2 * _e + _Xp) / (2 * _Xp))*100; // Stosunek proporcji e do _Xp
		}

		for (int j = 0; j <= 100; j += 5)
		{

			if (_cv == 0)
			{
				PORTC = ~(0x01 << 3);
				break;
			}
			if (j <= _cv)
			{
				PORTC = (0x01 << 3);
			}
			else
			{
				PORTC = ~(0x01 << 3);
			}
			_delay_ms(T0*50);
		}

		//przyciski
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
			_Xp = 30;
		}
		if (!(PINB & (1 << PB0)))
		{
			_Xp = 40;
		}

		LCD2x16_pos(1, 1);
		sprintf(tmp, "sp=%2d%% PV=%3d.%1d%%  ", (int)_sp, _ipv, _decpv);
		for (i = 0; i < 16; i++)
			LCD2x16_putchar(tmp[i]);

		LCD2x16_pos(2, 1);
		sprintf(tmp, "Xp=%2d%%  E=%3d.%1d%%   ", _Xp, (int)_e, dec_e);
		for (i = 0; i < 16; i++)
			LCD2x16_putchar(tmp[i]);
		delay_ms(50);
	}

	return 0;
}