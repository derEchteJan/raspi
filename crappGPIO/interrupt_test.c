#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"

#define TEST_PIN 18

void main() {
	
	// Setup
	setup_io();
	for(int i=0; i<22; i++) {
		INP_GPIO(i);
		OUT_GPIO(i);
	}
	// pin 21 as input and pulldown and high
	INP_GPIO(TEST_PIN);
	//GPIO_PULL &= ~(1 << TEST_PIN);
	GPIO_PULL |= (1 << TEST_PIN);
	//GPIO_SET = 1 << TEST_PIN;


}

void onButtonPressed() {
	printf("yeetus deletus");
}
