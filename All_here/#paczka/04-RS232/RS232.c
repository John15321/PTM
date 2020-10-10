/**************************************/
/*              ARE 2008              */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

#define F_CPU            1000000ul
#define UART_BAUD         2400ul
#define UART_CONST        (F_CPU/(16ul*UART_BAUD)-1)

#include <avr/io.h>
#include <avr/interrupt.h>


// Fubkcja wysylajaca string
void UART_SEND_string(char *s){
	do{
		while ( !( UCSRA & (1<<UDRE)) );
		UDR = *s;
	}while(*s++!='\0');
}

// Przerwanie wywolane zakonczeniem odbioru
ISR(USART_RXC_vect)
{ 
	UDR;
	UART_SEND_string("To ja, Twoj kontroler :)\n\r");
}

int main(void)
{
DDRD=0xfe;
PORTD=0xff;

// wlaczenie przerwan
SREG=(1<<SREG_I);

//konfiguracja portu szeregowego
UBRRH = (unsigned char)(UART_CONST>>8);
UBRRL = (unsigned char)UART_CONST;
UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); //wlaczony nadajnik, odbiornik, przerwanie od odbioru

while(1){}
return 0;
}
