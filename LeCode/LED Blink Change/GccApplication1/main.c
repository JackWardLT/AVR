/*
 * GccApplication1.c
 *
 * Created: 07.01.2024 16:09:29
 * Author : Lars
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL  // Adjust as per your clock
#include <util/delay.h>
#define LEDPIN PD4
#define OLP PD4
#define ILP PB1

void f();
void s();
void Task1();
void Task2();

int BP = 0;





int main(void)
{


	while (1)
	{
		//Task1();
		Task2();
	}
}

void Task2(){
	
	if(bit_is_clear(PINB, ILP)){
		BP++;
		if (BP == 1)
		{
			s();
		}
		if (BP == 2)
		{
			f();
		}
		else BP = 0;
	}
}


/************************************************************************/
/*	Task 1 | Lecture 3                                                  */
/************************************************************************/

void Task1(){
	DDRB &= ~(1 << PB1);
	DDRD |= (1 << LEDPIN);
	PORTD |= (1 << PB1);
	
	if (bit_is_clear(PINB, PB1)) f();
	else s();	
}

void f(){
	PORTD  |= (1 << LEDPIN);
	_delay_ms(500);
	PORTD &= ~(1 << LEDPIN);
	_delay_ms(500);
}

void s(){
	PORTD  |= (1 << LEDPIN);
	_delay_ms(2000);
	PORTD &= ~(1 << LEDPIN);
	_delay_ms(2000);
}