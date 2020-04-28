#include <stdio.h>
#include <unistd.h>
#include "framebuffer.h"

#define DELAY 500000

void main() {

	// Setup
	setup_framebuffer();

	int rectangles[] = {
		/* J */
		100, 100, 300, 100,
		400, 100, 100, 600,
		200, 700, 200, 100,
		100, 600, 100, 100,
		
		/* A */
		600, 200, 100, 600,
		700, 100, 200, 100,
		900, 200, 100, 600,
		700, 400, 200, 100,

		/* N */
		1100, 100, 100, 700,
		1200, 200, 100, 100,
		1300, 300, 100, 100,
		1400, 100, 100, 700
	};

	for(int i = 0; i < 12; i ++) {
		int ind = i << 2;
		fillRect(rectangles[ind], rectangles[ind + 1], rectangles[ind + 2], rectangles[ind + 3], COLOR_BLUE);
		usleep(DELAY);
	}
	for(int i = 0; i < 12; i ++) {
		int ind = i << 2;
		int offx = 20;
		int offy = 20;
		fillRect(rectangles[ind] + offx, rectangles[ind + 1] + offy, rectangles[ind + 2], rectangles[ind + 3], COLOR_GREEN);
		usleep(DELAY);
	}
	for(int i = 0; i < 12; i ++) {
		int ind = i << 2;
		int offx = 40;
		int offy = 40;
		fillRect(rectangles[ind] + offx, rectangles[ind + 1] + offy, rectangles[ind + 2], rectangles[ind + 3], COLOR_RED);
		usleep(DELAY);
	}

	/*

	fillRect(100, 100, 300, 400, COLOR_RED);

	usleep(DELAY);

	drawRect(100, 100, 300, 400, COLOR_BLUE);
	drawRect(100 - 1, 100 - 1, 300 + 2, 400 + 2, COLOR_GREEN);

	usleep(DELAY);

	fillCircle(500, 500, 300, COLOR_WHITE);

	*/

	printf("you should be happy now!");
}
