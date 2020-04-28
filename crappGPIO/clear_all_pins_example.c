#include <stdio.h>
#include <unistd.h>
#include "lib/crappgpio.h"

#define PIN_COUNT 40

void clear_all_pins() {
	for(int i = 0; i <= PIN_COUNT; i++) { // all pins output and off
		OUT_GPIO(i);
		GPIO_CLR |= 0x1 << i;
	}
}

void main() {
	setup_io();
	clear_all_pins();
	printf("pins cleared\n");
	return;
}


