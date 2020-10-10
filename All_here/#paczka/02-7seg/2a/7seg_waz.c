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
//char waz[] = { 0xfe, 0xfd, 0xbf, 0xef, 0xf7, 0xfb, 0xbf, 0xdf };
char waz[] = { 0x7f, 0xbf, 0xfd, 0xf7, 0xef, 0xdf, 0xfd, 0xfb };

PORTD=0xFF;
DDRD=0xFF;

int ms=100;                          

while(1)
	{
	for(int i=0;i<8;i++)
		{
		PORTD=waz[i];
		delay_ms(ms);
		}
	};

return(0);
}
