#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"

#define MEASURE_DELAY 100000 // in ys
#define TEST_PIN 16

void main() {
	
	// Setup
	setup_io();
	
	// test pin as input, pulldown and high
	INP_GPIO(TEST_PIN);
	//GPIO_PULL &= ~(1 << TEST_PIN);
	GPIO_PULL |= (1 << TEST_PIN);
	GPIO_SET = 1 << TEST_PIN;


	// loop
	int c = 0;
	while(1) {
		while(GET_GPIO(TEST_PIN) > 0) c++;
		c = 0;
		while(GET_GPIO(TEST_PIN) == 0) c++;
		while(GET_GPIO(TEST_PIN) > 0) c ++;
		printf("%d\n", c / 1000);
		c = 0;
		
		/*usleep(MEASURE_DELAY);
		int value = GET_GPIO(TEST_PIN) > 0;
		printf("%d\n", value);*/
	}
}
