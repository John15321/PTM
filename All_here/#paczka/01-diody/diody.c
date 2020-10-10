/**************************************/
/*              ARE 2009              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

#define F_CPU 1000000UL  // 1 MHz
//#define F_CPU 14.7456E6
#include <util/delay.h>
#include <avr/io.h>

void delay_ms( int ms)
	{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
		_delay_ms(1);
	}


int main(void)
{
//ustalenie kierunku pinow
DDRD=0xFF;

//zdefiniowanie zmiennej odpowiadajacej za opoznienia
int ms=100;
int i=0;

//ustawienie stanu poczatkowego portu
PORTD=0x03;

//"biegajace" diody
while(1)
	{
	for(i=0;i<6;i++)
	  {
	  PORTD=~(0x03<<i);
	  delay_ms(ms);
	  }
	for(i=6;i>0;i--)
	  {
	  PORTD=~(0x03<<i);
	  delay_ms(ms);
	  }
	};

return(0);
}
