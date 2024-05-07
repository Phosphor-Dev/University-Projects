/*
 * GccApplication1.c
 *
 * Created: 4/20/2022 5:29:13 PM
 * Author : steve
 */ 
/////////////
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);

void avr_wait(unsigned short msec);
/////////////

avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{

    DDRB = 0xff;
	DDRD = 0x00;
    while (1) 
    {
		if (GET_BIT(PIND,6) == 0) {
			avr_wait(500);
			PORTB = 0xff;
			avr_wait(500);
			PORTB = 0x00;
		}
		//PORTB = 0xff;
		//_delay_ms(100);
		//PORTB = 0x00;
		//_delay_ms(100);
	}
}

