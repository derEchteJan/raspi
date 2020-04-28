#include "framebuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int mem_fd;
void *framebuffer_map;
char *framebuffer;

void setup_framebuffer() {
	printf("framebuffer memory setup");
	if((mem_fd = open("/dev/fb0", O_RDWR|O_SYNC) ) < 0 ) {
		printf("\nerror: cant open /dev/fb0 \n");
		printf("try to run the programm with sudo\n");
		exit(-1);
	}
	printf(".");
	framebuffer_map = mmap(
		NULL,
		BLOCK_SIZE,
		PROT_READ|PROT_WRITE,
		MAP_SHARED,
		mem_fd,
		0
	);
	printf(".");
	close(mem_fd);
	if (framebuffer_map == MAP_FAILED) {
		printf("\nmmap error: %d\n", (int)framebuffer_map);
		exit(-1);
	}
	printf(".");
	framebuffer = (char *)framebuffer_map;
	printf("complete.\n");
}

/* Drawing Functions */

void fillRect(int x, int y, int w, int h, int color) {
	int xMax = x + w;
	int yMax = y + h;
	for (int xc = x; xc <= xMax; xc++) {
		for (int yc = y; yc <= yMax; yc++) {
			int offset = xc + SCREEN_W * yc;
			SCREEN_RED(offset) = (color >> 16) & 0xFF;
			SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
			SCREEN_BLUE(offset) = color & 0xFF;
		}
	}
}

void drawRect(int x, int y, int w, int h, int color) {
	int xMax = x + w;
	int yMax = y + h;
	int xc, yc, buf;
	buf = SCREEN_W * y;
	for (xc = x; xc < xMax; xc++) {
		int offset = xc + buf;
		SCREEN_RED(offset) = (color >> 16) & 0xFF;
		SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
		SCREEN_BLUE(offset) = color & 0xFF;
	}
	buf = SCREEN_W * yMax;
	for (xc = x; xc < xMax; xc++) {
		int offset = xc + buf;
		SCREEN_RED(offset) = (color >> 16) & 0xFF;
		SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
		SCREEN_BLUE(offset) = color & 0xFF;
	}
	xc = x;
	for (yc = y + 1; yc < yMax; yc++) {
		int offset = xc + yc * SCREEN_W;
		SCREEN_RED(offset) = (color >> 16) & 0xFF;
		SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
		SCREEN_BLUE(offset) = color & 0xFF;
	}
	xc = xMax;
	for (yc = y; yc <= yMax; yc++) {
		int offset = xc + yc * SCREEN_W;
		SCREEN_RED(offset) = (color >> 16) & 0xFF;
		SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
		SCREEN_BLUE(offset) = color & 0xFF;
	}
}

void fillCircle(int mx, int my, int r, int color) {
	int rSquared = r * r;
	for (int xc = mx - r; xc <= mx + r; xc++) {
		int dx = mx - xc;
		int dxSquared = dx * dx;
		for (int yc = my - r; yc <= my + r; yc++) {
			int dy = my - yc;
			int dySquared = dy * dy;
			if (dxSquared + dySquared <= rSquared) {
				int offset = xc + SCREEN_W * yc;
				SCREEN_RED(offset) = (color >> 16) & 0xFF;
				SCREEN_GREEN(offset) = (color >> 8) & 0xFF;
				SCREEN_BLUE(offset) = color & 0xFF;
			}
		}
	}
}
