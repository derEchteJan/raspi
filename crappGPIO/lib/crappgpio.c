#include "crappgpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;

void setup_io() {
	printf("gpio memory setup");
	if((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0 ) {
		printf("\nerror: cant open /dev/mem \n");
		printf("try to run the programm with sudo\n");
		exit(-1);
	}
	printf(".");
	gpio_map = mmap(
		NULL,
		BLOCK_SIZE,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		mem_fd,
		GPIO_BASE
	);
	printf(".");
	close(mem_fd);
	if (gpio_map == MAP_FAILED) {
		printf("\nmmap error: %d\n", (int)gpio_map);
		exit(-1);
	}
	printf(".");
	gpio = (volatile unsigned *)gpio_map;
	printf("complete.\n");
}


