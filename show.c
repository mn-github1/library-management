#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include "show.h"

static struct fb_var_screeninfo vinfo;
static char *psrc_mem = NULL;
static char *pmem_mem;

void fb_init(scrern_info *info)
{
	int fd = open("/dev/fb0", O_RDWR);
	if (-1 == fd){
		perror("open fd err!\n");	
	}
	ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
#if 1	
	printf("vir_x = %d, vir_y = %d\n",
			vinfo.xres_virtual,
			vinfo.yres_virtual);
	printf("xrex = %d, yres = %d\n",
			vinfo.xres,
			vinfo.yrex);
	printf("col = %d\n", vinfo.bits_per_pixel);
#endif
	info->w = vinfo.xres;
	info->h = vinfo.yres;
	info->bits_per_pixel = vinfo.bits_per_pixel;

	long src_size = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
	
	psrc_mem = mmap(NULL, src_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	pmem_mem = malloc(src_size);

	col bk;
	bk.l = RGB_WITHE;

	clr_src(bk);
}

void show_point(int x, int y, col c)
{
	if (x > vinfo.xres_virtual)
		return;
	if (y > vinfo.yres_virtual)
		return;

#if COL_DEPTH == 24
	unsigned int *p = (void *)(psrc_mem + ((y * vinfo.xres_virtual + x) * sizeof(int)));
#else
	unsigned short *p = (void *)(psrc_mem + ((y * vinfo.xres_virtual + x) * sizeof(short)));
#endif
	*p = c.l;
}
