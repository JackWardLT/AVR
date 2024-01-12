/*
*
* Created: 07.01.2024 19:55:22
* Author : Lars
*/
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL // Clock frequency

#define LED1 PB0 // First LED pin
#define LED2 PB1 // Second LED pin
#define BUTTON_PIN PB2 // Button pin

uint8_t debounce(uint8_t pinName, uint8_t pinNumber) {
	if (bit_is_clear(pinName, pinNumber)) {
		_delay_ms(50); // 5 ms delay for debouncing
		if (bit_is_clear(pinName, pinNumber)) {
			return 1; // Confirmed button press
		}
	}
	return 0; // No button press detected or debouncing not passed
}

void toggleLEDs() {
	PORTB ^= (1 << LED1); // Toggle LED1
	PORTB ^= (1 << LED2); // Toggle LED2
}

int main(void) {
	// Set LED pins as outputs
	DDRB |= (1 << LED1) | (1 << LED2);
	// Set button pin as input with pull-up enabled
	DDRB &= ~(1 << BUTTON_PIN);
	PORTB |= (1 << BUTTON_PIN);

	// Ensure LED1 is initially on and LED2 is off
	PORTB |= (1 << LED1);
	PORTB &= ~(1 << LED2);

	uint8_t buttonPressedInstructions = 0;

	while (1) {
		// Use the debounce function to check for button press
		if (debounce(PINB, BUTTON_PIN)) {
			if (buttonPressedInstructions == 0) {
				toggleLEDs();
				buttonPressedInstructions = 1; // Mark that the button instruction has been executed
			}
			} else {
			buttonPressedInstructions = 0; // Reset the instruction flag
		}
		// No need to delay here since debounce function already has a delay
	}
}


