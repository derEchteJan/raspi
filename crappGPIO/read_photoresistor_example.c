#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"


#define DELAY_ONE_S 1000000	// in ys
#define DELAY_ONE_MS 1000		// in ys
#define CAL_MAX_VAL 465
#define TEST_PIN 12		// pin number to measure on


int measure_light(int pin_nr) {
	// charge capacitor for 100 ms
	OUT_GPIO(pin_nr);				// dir output
	GPIO_SET = 1 << pin_nr;			// output high
	usleep(DELAY_ONE_MS * 100);		// wait

	// set pin to input
	INP_GPIO(pin_nr);				// dir input
	GPIO_PULL |= (1 << pin_nr); 	// pull up
	GPIO_SET = 1 << pin_nr; 		// output high
	
	// busy loop until capacitor has discarged and input is read low
	int cycles = 0;
	int pin_state = GET_GPIO(TEST_PIN);
	while(pin_state > 0) {
		usleep(DELAY_ONE_MS);
		pin_state = GET_GPIO(TEST_PIN);
		cycles++;
	}
	
	// calculate to percent
	int value = (CAL_MAX_VAL - cycles) * 100 / CAL_MAX_VAL;
	if(value < 0) value = 0;
	return value;
}

void clear_all_pins() {
	for(int i = 0; i <= 40; i++) { // all pins output and off
		OUT_GPIO(i);
		GPIO_CLR |= 0x1 << i;
	}
}


void main() {
	
	// Setup
	setup_io();
	clear_all_pins();
	
	printf("press Ctrl+C to quit\n");
	
	// measure loop
	while(1) {
		int light_value = measure_light(TEST_PIN);
		printf("%d\n", light_value);
		usleep(DELAY_ONE_S >> 1);
	}
}


