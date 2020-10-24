/**************************************/
/*              ARE 2008              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

#define F_CPU 8000000UL // 1 MHz
#define __AVR_ATmega32__

//#define F_CPU 14.7456E6
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

//RS PA0
//RW PA1
//E  PA2
//DATA PD

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
	delay_ms(1);
	PORTC &= ~(1 << E);
	_delay_us(120);
}

int _sp = 40;
int _h = 8;
int _pv;
int _e;

int _ipv;
int _decpv;

int main(void)
{
	char tmp[16];

	int i;
	int j = 1;

	DDRD = 0xff;
	PORTD = 0x00;
	DDRC = 0xff;
	PORTC = 0x00;
	DDRB = 0x00;
	PORTB = 0xff;

	_delay_ms(500);

	LCD2x16_init();
	LCD2x16_clear();

	ADMUX = 0x40;
	ADCSRA = 0xe0;

	while (1)
	{
		// Start an ADC conversion by setting ADSC bit (bit 6)
		ADCSRA = ADCSRA | (1 << ADSC);

		// Wait until the ADSC bit has been cleared
		while(ADCSRA & (1 << ADSC));

		_pv = ADC;
		_ipv = (_pv / 1024)*100;
		_e = _sp - _ipv;
		_decpv = (_pv - _ipv);

		// zapalanie diody
		if (_e > _h / 2)
		{
			PORTC = (0x01 << 5);
		}

		// gaszenie diody
		if (_e < -_h / 2)
		{
			PORTC = ~(0x01 << 5);
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
			_h = 8;
		}
		if (!(PINB & (1 << PB0)))
		{
			_h = 10;
		}

		//LCD2x16_clear();
		LCD2x16_pos(1, 1); //bylo 2,1
		//sprintf(tmp,"Dzialam juz %2is ",j);
		sprintf(tmp, "SP=%2d PV=%3d.%1d%% www", _sp, _ipv, _decpv);
		j++;
		for (i = 0; i < 16; i++)
			LCD2x16_putchar(tmp[i]);

		LCD2x16_pos(2, 1); //bylo 2,1
		//sprintf(tmp,"Dzialam juz %2is ",j);
		sprintf(tmp, "H=%2d E=%3d.%1d%%wwwww", _h, _e, _decpv);
		for (i = 0; i < 16; i++)
			LCD2x16_putchar(tmp[i]);
		delay_ms(500); // bylo 1000
	}

	return 0;
}