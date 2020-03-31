#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#define SCREEN_W 1824
#define SCREEN_H 958
#define BLOCK_SIZE ((SCREEN_W * SCREEN_H) << 2) // w * h * 4B per pixel
#define SCREEN_RED(o) *(framebuffer+((o)<<2)+2)
#define SCREEN_GREEN(o) *(framebuffer+((o)<<2)+1)
#define SCREEN_BLUE(o) *(framebuffer+((o)<<2))

#define COLOR_WHITE	0xFFFFFF
#define COLOR_RED 	0xFF0000
#define COLOR_GREEN 	0x00FF00
#define COLOR_BLUE 	0x0000FF

char *framebuffer;

void setup_framebuffer();
void fillRect(int x, int y, int w, int h, int color);
void drawRect(int x, int y, int w, int h, int color);
void fillCircle(int mx, int my, int r, int color);

#endif
