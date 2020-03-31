#include <stdio.h>
#include <unistd.h>
#include "gpio.h"

#define DELAY 200000

void main() {

	// setup
	setup_io();
	int i = 0;
	for (i=20; i<=22; i++) {
		INP_GPIO(i);
		OUT_GPIO(i);
	}

	// run forever
	printf("press ctrl + C to quit.\n");

	while (1) {

		// on and off in a row

		for (int n=0; n < 5; n++) {
			for(i=20; i<=22; i++) {
				GPIO_SET = 1 << i;
				usleep(DELAY);
			}
			for(i=20; i<=22; i++) {
				GPIO_CLR = 1 << i;
				usleep(DELAY);
			}
		}
		for (int n=0; n<5; n++) {
			GPIO_SET = 7 << 20;
			usleep(DELAY);
			GPIO_CLR = 7 << 20;
			usleep(DELAY);
		}
		for (int n=0; n<5; n++) {
			for (i=20; i<=22; i++) {
				GPIO_SET = 1 << i;
				usleep(DELAY);
				GPIO_CLR = 1 << i;
				usleep(DELAY);
			}
		}
	} // while true
	return;
} // main
