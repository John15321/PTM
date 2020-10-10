/**************************************/
/*              ARE 2008              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

#define F_CPU 1000000UL  // 1 MHz
//#define F_CPU 14.7456E6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <string.h>

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

//RS PA0
//RW PA1
//E  PA2
//DATA PD

#define RS 0
#define RW 1
#define E  2

void LCD2x16_init(void)
{
PORTA &= ~(1<<RS);
PORTA &= ~(1<<RW);

PORTA |= (1<<E);
PORTD = 0x38;   // dwie linie, 5x7 punktow
PORTA &=~(1<<E);
_delay_us(120);

PORTA |= (1<<E);
PORTD = 0x0e;   // wlacz wyswietlacz, kursor, miganie
PORTA &=~(1<<E);
_delay_us(120);

PORTA |= (1<<E);
PORTD = 0x06;
PORTA &=~(1<<E);
_delay_us(120);
}

void LCD2x16_clear(void){
PORTA &= ~(1<<RS);
PORTA &= ~(1<<RW);

PORTA |= (1<<E);
PORTD = 0x01;
PORTA &=~(1<<E);
delay_ms(120);
}

void LCD2x16_putchar(int data)
{
PORTA |= (1<<RS);
PORTA &= ~(1<<RW);

PORTA |= (1<<E);
PORTD = data;
PORTA &=~(1<<E);
_delay_us(120);
}

void LCD2x16_pos(int wiersz, int kolumna)
{
PORTA &= ~(1<<RS);
PORTA &= ~(1<<RW);

PORTA |= (1<<E);
delay_ms(1);
PORTD = 0x80+(wiersz-1)*0x40+(kolumna-1);
delay_ms(1);
PORTA &=~(1<<E);
_delay_us(120);
}



int main(void){
char www[16] = "www-> are.net.pl";
char email[16] = "biuro@are.net.pl";
char tmp[16];

int i;
int j=4;

DDRD = 0xff;
PORTD = 0x00;
DDRA = 0xff;
PORTA = 0x00;

_delay_ms(200);

LCD2x16_init();
LCD2x16_clear();


    for(i=0;i < 16;i++)
		LCD2x16_putchar(www[i]);
	LCD2x16_pos(2,1);
	for(i=0;i < 16;i++)
		LCD2x16_putchar(email[i]);

delay_ms(3000);
LCD2x16_clear();
for(i=0;i < 16;i++)
	LCD2x16_putchar(www[i]);

while(1)
	{
	//LCD2x16_clear();
	LCD2x16_pos(2,1);
	sprintf(tmp,"Dzialam juz %2is ",j);
	j++;
	for(i=0;i < 16;i++)
		LCD2x16_putchar(tmp[i]);
	delay_ms(1000);   
	}

return 0;
}