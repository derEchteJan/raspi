/*
 *  Build with: gcc -o <filename>.o lib/crappgpio.h lib/crappgpio.c output_led_example.c
 * 	Run with: sudo ./<filename>.o
 */

#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"

#define DELAY 200000  // in ns
#define REPEAT_CYCLES 3
#define FIRST_PIN 20
#define LAST_PIN 22
#define PIN_COUNT 8

void main() {
	
	// connected pin numbers in order from right to left
	int led_pins[PIN_COUNT] = {19, 6, 0, 11, 10, 22, 17, 4};

	// setup memory handle
	setup_io();
	
	// first clear all pins 0 - 22
	int i = 0; // pin index
	int pin_nr = 0;
	for (i = 0; i < PIN_COUNT; i++) {
		pin_nr = led_pins[i];
		OUT_GPIO(pin_nr);
		GPIO_CLR = 1 << pin_nr;
	}

	// run forever
	printf("press ctrl + C to quit.\n");

	while (1) {

		// on and off in a row from FIRST_PIN to LAST_PIN
		
		// set on from left to right, then off from left to right
		for (int n = 0; n < REPEAT_CYCLES; n++) {
			for(i = 0; i < PIN_COUNT; i++) {
				pin_nr = led_pins[i];
				GPIO_SET = 1 << pin_nr;
				usleep(DELAY);
			}
			for(i = 0; i < PIN_COUNT; i++) {
				pin_nr = led_pins[i];
				GPIO_CLR = 1 << pin_nr;
				usleep(DELAY);
			}
		}
		// flash all leds simultanously
		for (int n = 0; n < REPEAT_CYCLES; n++) {
			GPIO_SET = 0xFFFFFF; // Set to ON first 8 pins
			usleep(DELAY);
			GPIO_CLR = 0xFFFFFF;
			usleep(DELAY);
		}
		// flash on then off all leds from left to right
		for (int n = 0; n < REPEAT_CYCLES; n++) {
			for (int i = 0; i < PIN_COUNT; i++) {
				pin_nr = led_pins[i];
				GPIO_SET = 1 << pin_nr;
				usleep(DELAY);
				GPIO_CLR = 1 << pin_nr;
				usleep(DELAY);
			}
		}
	} // while true
	return;
} // main
