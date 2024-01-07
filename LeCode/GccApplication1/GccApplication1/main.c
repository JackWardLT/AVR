/*
 * GccApplication1.c
 *
 * Created: 07.01.2024 16:09:29
 * Author : Lars
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL  // Adjust as per your clock
#include <util/delay.h>

void f(){
	PORTD  |= (1 << PD6);
	_delay_ms(500);
	PORTD &= ~(1 << PD6);
	_delay_ms(500);
}

void s(){
	PORTD  |= (1 << PD6);
	_delay_ms(2000);
	PORTD &= ~(1 << PD6);
	_delay_ms(2000);	
}

int main(void)
{
	DDRB &= ~(1 << PB0);
	DDRD |= (1 << PD6); 
	PORTD |= (1 << PB0);

	while (1)
	{
		if (bit_is_clear(PINB, PB0)) f();
		else s();
	}
}
