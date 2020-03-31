/*//#define BCM_PERI_BASE	0x20000000	// for raspberrypi 1
#define BCM_PERI_BASE	0x3F000000	// for raspberrypi 2, 3
#define GPIO_BASE		(BCM_PERI_BASE + 0x200000)
*/
#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;
/*
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))	// GPSEL(n) 000, input mode
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))	// GPSEL(n) 001, output mode
#define GPIO_SET *(gpio+7)	// GPSET0
#define GPIO_CLR *(gpio+10)	// GPCLR0
*/
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
