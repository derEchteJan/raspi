#include <stdio.h>
#include <unistd.h>
#include "gpio.h"

#define DELAY 10000 // 10 ms
#define STEPS 10

void main() {
	
	// Setup
	setup_io();
	for(int i=0; i<22; i++) {
		INP_GPIO(i);
		OUT_GPIO(i);
	}
	// pin 21 as input and pulldown and high
	INP_GPIO(21);
	//GPIO_PULL &= ~(1 << 21);
	GPIO_PULL |= (1 << 21);
	GPIO_SET = 1 << 21;


	// loop

	int data[STEPS];
	while (1) {
		for (int n = 0; n < STEPS; n++) {
			usleep(DELAY / STEPS);
			data[n] = GET_GPIO(21);
		}
		printf("\nresults:\n");
		for (int n = 0; n < STEPS; n++) {
			if(data[n] != 0) {
				printf("-");
			} else {
				printf("_");
			}
		}
		printf("\n");
		usleep(3 * 1000 * 1000); // wait 3 s
	} // loop
}
