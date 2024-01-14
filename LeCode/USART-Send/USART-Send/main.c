/*
 * USART-Send.c
 *
 * Created: 14.01.2024 13:16:22
 * Author : Lars
 */ 

#define F_CPU 16000000UL // Set to your clock frequency
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)
// Task 2
void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8data, 2stop bit, even parity
	UCSRC = (1<<URSEL)|(1<<UPM1)|(1<<USBS)|(3<<UCSZ0);
}
// TASK 1
/*
void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8data, 1stop bit
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}
*/
void USART_Transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1<<UDRE)));
	// Put data into buffer, sends the data
	UDR = data;
}

int main(void) {
	USART_Init(MYUBRR); // Initialize USART with baud rate
	DDRA &= ~(1<<PA0); // Set PA0 as input
	PORTA |= (1<<PA0); // Enable pull-up resistor on PA0

	unsigned char buttonState = 0;
	unsigned char lastButtonState = (PINA & (1<<PA0)); // Initialize to the current state

	while(1) {
		// Read button state
		buttonState = PINA & (1<<PA0);

		// If button state changed and button is pressed
		if ((buttonState != lastButtonState) && (buttonState == 0)) {
			// Send a signal to toggle the LED
			USART_Transmit(0x01);
			// Simple debounce
			_delay_ms(50);
			// Wait for the button to be released to avoid multiple signals on one press
			while((PINA & (1<<PA0)) == 0){}
			_delay_ms(50); // Additional debounce delay after release
		}
		
		lastButtonState = buttonState;
	}
}

