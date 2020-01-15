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

