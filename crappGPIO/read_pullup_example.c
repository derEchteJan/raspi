#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"

#define DELAY 1000000 // in ms
#define TEST_PIN_A 23
#define TEST_PIN_B 24

void main() {
	
	// Setup
	setup_io();
	
	// pins as input and pulldown and high
	INP_GPIO(TEST_PIN_A);
	INP_GPIO(TEST_PIN_B);
	//GPIO_PULL &= ~(1 << TEST_PIN_A);
	GPIO_PULL |= (1 << TEST_PIN_A);
	GPIO_PULL |= (1 << TEST_PIN_B);
	GPIO_SET = 1 << TEST_PIN_A;
	GPIO_SET = 1 << TEST_PIN_B;


	// loop

	while (1) {
		int value_A = GET_GPIO(TEST_PIN_A);
		int value_B = GET_GPIO(TEST_PIN_B);
		if (value_A > 0)
			printf("1");
		else
			printf("0");
		if (value_B > 0)
			printf("1\n");
		else
			printf("0\n");
		usleep(DELAY);
	} // loop
}
