/*
 * USART.c
 *
 * Created: 13.01.2024 17:47:16
 * Author : Lars
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL // Adjust this if your F_CPU is different
#endif

#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8data, 2stop bit
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1<<UDRE)));
	// Put data into buffer, sends the data
	UDR = data;
}

unsigned char USART_Receive(void) {
	// Wait for data to be received
	while (!(UCSRA & (1<<RXC)));
	// Get and return received data from buffer
	return UDR;
}

int main(void) {
	USART_Init(MYUBRR); // Initialize USART with baud rate
	DDRB = 0xFF; // Set all PORT B pins as output (for LED)
	DDRA = 0x00; // Set all PORT A pins as input (for button)

	// Assuming button is connected to PA0 and LED to PB0
	PORTA = 0xFF; // Enable pull-up resistors for PORT A

	unsigned char buttonState = 0;
	unsigned char lastButtonState = 0;
	unsigned char ledState = 0;

	while(1) {
		// Read button state
		buttonState = PINA & 0x01; // Read only PA0

		// If button state changed and button is pressed
		if(buttonState != lastButtonState && buttonState == 0) {
			// Toggle LED state
			ledState = !ledState;
			// Send new LED state to other microcontroller
			USART_Transmit(ledState ? 0b01110000 : 0b00001111);
		}
		lastButtonState = buttonState;

		// Check if data is received
		if(UCSRA & (1<<RXC)) {
			unsigned char receivedData = USART_Receive();
			// If received data is the toggled state, toggle LED
			if(receivedData == 0b01110000 || receivedData == 0b00001111) {
				PORTB ^= 0x01; // Toggle PB0
			}
		}
		
		_delay_ms(50); // Debounce delay
	}
}
