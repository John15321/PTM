/**************************************/
/*              ARE 2008              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

#define F_CPU 1000000UL  // 1 MHz
//#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/io.h>

void delay_ms(int ms)
	{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
		_delay_ms(1);
	}

int main(void)
{
//char seg[] = {0xC0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };
char seg[] = {0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41, 0x1f, 0x01, 0x09, 0x11, 0xc1, 0xe5, 0x85, 0x61, 0x71 };
PORTD=0xFF;
DDRD=0xFF;

ADMUX=0x40;
ADCSRA=0xe0;

int ms=50;                          

while(1)
	{
	for(int i=0;i<0x10;i++)
		{
		PORTD=seg[ADC>>6];
		delay_ms(ms);
		}
	};

return(0);
}
