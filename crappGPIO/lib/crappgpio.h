#ifndef _CRAPPGPIO_H_
#define _CRAPPGPIO_H_


//#define BCM_PERI_BASE	0x20000000	// for raspberrypi 1
#define BCM_PERI_BASE	0x3F000000	// for raspberrypi 2, 3
#define GPIO_BASE	(BCM_PERI_BASE + 0x200000)
#define PAGE_SIZE 	(4*1024)
#define BLOCK_SIZE 	(4*1024)

volatile unsigned *gpio;

#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))	// GPSEL(n) 000, input mode
#define OUT_GPIO(g) *(gpio+((g)/10)) |= (1<<(((g)%10)*3))	// GPSEL(n) 001, output mode
#define GPIO_SET *(gpio+7)	// GPSET0
#define GPIO_CLR *(gpio+10)	// GPCLR0
#define GET_GPIO(g) (*(gpio+13)&(1<<g))		// GPLEVn
#define GPIO_PULL *(gpio+37)	// 

void setup_io();

#endif
