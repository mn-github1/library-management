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
	
	printf("vir_x = %d, vir_y = %d\n",
			vinfo.xres_virtual,
			vinfo.yres_virtual);
	printf("xrex = %d, yres = %d\n",
			vinfo.xres,
			vinfo.yrex);
	printf("col = %d\n", vinfo.bits_per_pixel);
	info->w = vinfo.xres;
}
