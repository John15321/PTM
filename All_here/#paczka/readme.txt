/**************************************/
/*           ARE 2007-2009            */
/*      e-mail: biuro@are.net.pl      */
/*      www   : are.net.pl            */
/**************************************/

Makefile jest przygotowany dla 
programatora USBasp. Jeœli u¿ytkownik 
korzysta z STK200, to nale¿y wpis:
AVRDUDE_PROGRAMMER = USBasp
zamieniæ na:
AVRDUDE_PROGRAMMER = stk200

Jeœli u¿ytkownik korzysta z ATmega32, 
to nale¿y wpis:
MCU = atmega16
zamieniæ na:
MCU = atmega32

W przypadku problemów nale¿y pisaæ 
na wskazany wy¿ej adres.

Nale¿y spodziewaæ siê aktualizacji.

Historia:
20090624 - ujednolicenie plików Makefile
         - uzupe³nienie schematu dla 02-7seg
         - uzupe³nienie schematu dla 03-ADC
         - dodanie programu do osb³ugi serwomechanizmu
20090417 - uproszczenie programu 01-diody
         - aktualizacja programu 02-7seg
         - aktualizacja programu 03-ADC
         - aktualizacja programu 04-RS232
20090107 - poprawka programu 01-diody
20081209 - dodanie programu do obs³ugi LCD2x16
20081202 - dodanie programu do obs³ugi RS232
         - dodanie schematów po³¹czeñ do starej wersji p³ytki
20081128 - pierwsza edycja paczki