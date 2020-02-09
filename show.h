#ifndef __SHOW_H
#define __SHOW_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef int LONG;

typedef struct  tagBITMAPFILEHEADER {
	unsigned char reserv[14];
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYpelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct _tag_bmp {
	int width;
	int height;
	void *data;
}tag_bmp;


#define PI 3.1415926

#define RGB_WITHE 0x00ffffff
#define RGB_BLACK 0x00000000
#define RGB_TRANS 0xff000000
#define RGB_GRAY  0x00606060

#define COL_DEPTH 24

#if COL_DEPTH == 24
struct tag_rgb {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char null;
};
#else
struct tag_rgb {
	unsigned short b:5;
	unsigned short g:6;
	unsigned short r:5;
};
#endif

typedef union {
	struct tag_rgb rgb;
#if COL_DEPTH == 24
	unsigned int l;
#else
	unsigned short l;
#endif
}col;

typedef struct {
	int x;
	int y;
}point;

typedef struct {
	int x;
	int y;
	int w;
	int h;
}rect;

#define ICON_WIDTH 100
#define ICON_HEIGHT 128

typedef struct tag_icon{
	int select;
	int type;
	rect m_rect;
	tag_bmp *pbmp;
	char name[256];
	col f;
	col bk;
	struct tag_icon *next;
}icon;

#define FONT_HEIGHT 28
#define FONT_WIDTH_PER_BYTE 8
typedef struct {
	int w;
	int h;
	int bits_per_pixel;
}screen_info;

extern void show_point(int x, int y, col c);
extern void fb_init(screen_info *info);
extern void copy_screen(rect m_rect, int direct);
extern void draw_h_line(int x0, int y0, int width, col c);
extern void draw_s_line(int x0, int y0, int height, col c);
extern void draw_line(int x0, int y0, int x1, int y1, col c);
extern void draw_line_point(point s, point e, col c);
extern void fill_rect(int x0, int y0, int width, int height, col c);
extern void draw_rect(int x0, int y0, int width, int height, col c);
extern void clr_src(col c);
extern void draw_circle_n(point pt0, int r, int n, col c);
extern void poly_line(point *pt, int n, col c);
extern void draw_a_ascii(int x0, int y0, char ch, col f, col bk);
extern void draw_a_ascii_by_zimo(int x0, int y0, unsigned char *zimo, col f, col bk);
extern void draw_string(int x0, int y0, char *str, col f, col bk);
extern void draw_a_chinese_by_zimo(int x0, int y0, unsigned char *zimo, col f, col bk);
extern void draw_a_chinese(int x0, int y0, unsigned char code[2], col f, col bk);
extern void draw_chinese(int x0, int y0, unsigned char *str, col f, col bk);
extern void draw_text(int x0, int y0, unsigned char *str, col f, col bk);
extern void draw_text_n(int x0, int y0, unsigned char *str, int n, col f, col bk);
extern tag_bmp *load_bmp(char *filename);
extern void show_bmp (int x0, int y0, tag_bmp *p);
extern void show_bmp_reverse(int x0, int y0, tag_bmp *p);
extern void free_bmp(tag_bmp *p);
extern void show_cursor(int x0, int y0, tag_bmp *p);
extern void draw_icon (icon *m_icon);
extern icon *create_icon(rect m_rect, tag_bmp *p, char *name, col f, col bk, int type);
#endif
