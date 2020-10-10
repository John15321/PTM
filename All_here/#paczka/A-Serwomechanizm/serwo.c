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
	
void delay_us(int us)
	{
	volatile long unsigned int i;
	for(i=0;i<us;i++)
		_delay_us(1);
	}


int main(void){
DDRB = 0xff;
PORTB = 0x00;

TCCR0 = 0x6b;
OCR0 = 23;


while(1)
	{
	OCR0=23;
	delay_ms(3000);
	OCR0=15;
	delay_ms(3000);
	OCR0=23;
	delay_ms(3000);
	OCR0=31;
	delay_ms(3000);
	}

return 0;
}