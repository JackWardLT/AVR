/*
 * USART-GET.c
 *
 * Created: 14.01.2024 13:22:26
 * Author : Lars
 */ 

#define F_CPU 16000000UL // 16 MHz, adjust if different

#include <avr/io.h>
#include <util/delay.h>



#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) - 1)

//TASK 2
void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8data, 2stop bit, even parity
	UCSRC = (1<<URSEL)|(1<<UPM1)|(1<<USBS)|(3<<UCSZ0);
}

//TASK 1
/*
void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set frame format: 8-bit data, 1 stop bit
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}
*/
unsigned char USART_Receive(void) {
	// Wait for data to be received
	while (!(UCSRA & (1<<RXC)));
	// Get and return the received data from the buffer
	return UDR;
}

int main(void) {
	USART_Init(MYUBRR); // Initialize USART with the given baud rate
	DDRB = 0xFF; // Set all PORT B pins as output for the LED
	
	while (1) {
		unsigned char receivedData = USART_Receive();
		// If the received data is 0x01, toggle the LED on PB0
		if (receivedData == 0x01) {
			PORTB ^= (1<<PB0); // Toggle PB0
			_delay_ms(100); // A simple software debouncing
		}
	}
}
