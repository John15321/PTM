/**************************************/
/*           ARE 2007-2009            */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

Makefile jest przygotowany dla 
programatora USBasp. Je�li u�ytkownik 
korzysta z STK200, to nale�y wpis:
AVRDUDE_PROGRAMMER = USBasp
zamieni� na:
AVRDUDE_PROGRAMMER = stk200

Je�li u�ytkownik korzysta z ATmega32, 
to nale�y wpis:
MCU = atmega16
zamieni� na:
MCU = atmega32

W przypadku problem�w nale�y pisa� 
na wskazany wy�ej adres.

Nale�y spodziewa� si� aktualizacji.

Historia:
20090624 - ujednolicenie plik�w Makefile
         - uzupe�nienie schematu dla 02-7seg
         - uzupe�nienie schematu dla 03-ADC
         - dodanie programu do osb�ugi serwomechanizmu
20090417 - uproszczenie programu 01-diody
         - aktualizacja programu 02-7seg
         - aktualizacja programu 03-ADC
         - aktualizacja programu 04-RS232
20090107 - poprawka programu 01-diody
20081209 - dodanie programu do obs�ugi LCD2x16
20081202 - dodanie programu do obs�ugi RS232
         - dodanie schemat�w po��cze� do starej wersji p�ytki
20081128 - pierwsza edycja paczki