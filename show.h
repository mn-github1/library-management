#ifndef __SHOW_H
#define __SHOW_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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

tag_bmp *load_bmp(char *filename);

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

tag_bmp *load_bmp(char *filename);
void free_bmp(tag_bmp *p); 
void show_bmp (int x0, int y0, tag_bmp *p);
void clr_src(col c);
icon *create_icon(rect m_rect, tag_bmp *p, char *name, col f, col bk, int type);
void list_and_draw_dir(char *path, screen_info info, int x, int y);
#endif
