/*
 * L3T2.c
 *
 * Created: 07.01.2024 19:09:55
 * Author : Lars
 */ 
#include <avr/io.h>
#define F_CPU 1000000UL // 1 MHz, adjust this to your actual clock speed
#include <util/delay.h>

#define LEDPIN PB0 // Define the LED pin
#define BUTTONPIN PB1 // Define the button pin

void delay_ms_variable(uint16_t ms) {
	for(uint16_t i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void) {
	// Initialize LED pin as output
	DDRB |= (1 << LEDPIN);
	// Initialize button pin as input with pull-up enabled
	DDRB &= ~(1 << BUTTONPIN);
	PORTB |= (1 << BUTTONPIN);

	uint8_t buttonPressedInstructions = 0; // Flag for button press
	uint16_t delaySpeed = 1000; // Start with a 1 second delay

	while (1) {
		// Toggle the LED
		PORTB ^= (1 << LEDPIN);

		// Check if the button is pressed
		if (bit_is_clear(PINB, BUTTONPIN)) {
			// Debounce delay
			_delay_ms(50);
			// Check if the button is still pressed
			if (bit_is_clear(PINB, BUTTONPIN)) {
				if (buttonPressedInstructions == 0) {
					// Change the delay speed to fast blinking
					delaySpeed = 100;
					buttonPressedInstructions = 1; // Mark the instruction as executed
					} else {
					// Change the delay speed to slow blinking
					delaySpeed = 1000;
					buttonPressedInstructions = 0; // Reset the instruction flag
				}
				// Wait for the button to be released (additional debounce)
				while (bit_is_clear(PINB, BUTTONPIN));
			}
		}
		
		// Execute the variable delay
		delay_ms_variable(delaySpeed);
	}
}
