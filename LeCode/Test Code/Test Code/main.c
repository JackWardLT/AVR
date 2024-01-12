/*
 * Test Code.c
 *
 * Created: 09.01.2024 10:28:12
 * Author : Lars
 */ 


#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define the CPU clock speed (16MHz in this example)
// Remember to replace 16000000UL with the actual clock speed of your AVR

// Custom delay function to handle variable delays
void variable_delay_ms(uint16_t milliseconds) {
	while(milliseconds--) {
		_delay_ms(1); // delay for 1 ms
	}
}

int main(void) {
	// Variables
	uint8_t buttonPressedCounter = 0;
	uint16_t delaySpeed = 1000; // milliseconds

	// Initialize the I/O for the LED and button
	DDRB |= (1 << PB0); // Set PB0 as output for the LED
	DDRB &= ~(1 << PB1); // Set PB1 as input for the button
	PORTB |= (1 << PB1); // Enable pull-up resistor on PB1

	// Main loop
	while (1) {
		PORTB ^= (1 << PB0); // Toggle the LED on PB0

		// Check if button on PB1 is pressed (assuming active low)
		if (!(PINB & (1 << PB1))) {
			if (buttonPressedCounter == 0) { // If button pressed instructions have NOT been executed
				if (delaySpeed == 1000) { // If the speed of blinking is slow
					delaySpeed = 100; // Change the delay speed value to fast blinking
					} else {
					delaySpeed = 1000; // Change the delay speed value to slow blinking
				}
				buttonPressedCounter = 1; // Button pressed instructions have been executed (once)
			}
			} else {
			buttonPressedCounter = 0; // Button pressed instructions have NOT been executed
		}

		variable_delay_ms(delaySpeed); // Wait for the specified delay
	}
	return 0;
}
