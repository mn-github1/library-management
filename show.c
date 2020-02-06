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
//显示文件初始化
void fb_init(screen_info *info)
{
	int fd = open("/dev/fb0", O_RDWR); //打开显卡设备
	if (-1 == fd){
		perror("open fd err!\n");	
	}
	ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);//获得屏幕分辨率信息
#if 1	
	printf("vir_x = %d, vir_y = %d\n",  //打印当前设备信息
			vinfo.xres_virtual,
			vinfo.yres_virtual);
	printf("xrex = %d, yres = %d\n",
			vinfo.xres,
			vinfo.yres);
	printf("col = %d\n", vinfo.bits_per_pixel);
#endif
	info->w = vinfo.xres;
	info->h = vinfo.yres;
	info->bits_per_pixel = vinfo.bits_per_pixel;

	long src_size = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
	//显存映射
	psrc_mem = mmap(NULL, src_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	pmem_mem = malloc(src_size);

	col bk;
	bk.l = RGB_WITHE;//白色

	clr_src(bk);//清屏
}

//在屏幕上显示一个点
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

//显存和内存之间的数据拷贝
void copy_screen(rect m_rect, int direct)
{
	unsigned int *psrc , *pdst;
	int x, y;
	for (y = 0; y < m_rect.h; y++) {
		for (x = 0; x < m_rect.w; x++) {
			if (direct == 0) {
				psrc = (void *)(psrc_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x) * 4));
				pdst = (void *)(pmem_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x) * 4));
				*pdst = *psrc;
			} else {
				psrc = (void *)(pmem_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x) * 4));
				pdst = (void *)(psrc_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x) * 4));
				*pdst = *psrc;
			}
		}
	}
}

//在屏幕上显示横线
void draw_h_line(int x0, int y0, int width, col c)
{
	int i;
	for (i = 0; i < width; ++i) {
		show_point(x0 + i, y0, c);
	}

	return ;
}

//在屏幕上显示竖线
void draw_s_line(int x0, int y0, int height, col c)
{
	int i;
	for (i = 0; i < height; ++i) {
		show_point(x0, y0 + i, c);
	}

	return ;
}

//在屏幕上显示一条斜线
void draw_line(int x0, int y0, int x1, int y1, col c)
{
	int sx, sy, ex, ey;
	if (x0 > x1) {
		sx = x1;
		sy = x1;
		ex = x0;
		ey = y0;
	} else {
		sx = x0;
		sy = y0;
		ex = x1;
		ey = y1;
	}

	if (sy = ey) {
		draw_h_line(sx, sy, ex - sx, c);
		return ;
	}

	// 0 < k < 1
	double k = (double)(ey - sy) / (ex - sx);
	double b = sy - k * sx;
	if ((k <= 1.0) && (k >= -1.0)) {
		int x;
		double y;
		for (x = sx; x <= ex; ++x) {
			y = k * x + b;
			if (( y - (int)y) > 0.5) {
				y += 1;
			}
			show_point(x, y, c);
		}

		return ;
	}

	// k > 1
	if (y0 > y1) {
		sx = x1;
		sy = y1;
		ex = x0;
		ey = y0;
	} else {
		sx = x0;
		sy = y0;
		ex = x1;
		ey = y1;
	}	

	if (sx == ex) {
		draw_s_line(sx, sy, ey - sy, c);
		return ;
	}

	k = (double)(ex -sx) / (ey - sy);
	b = sx - k * sy;
	int y;
	double x;
	for (y = sy; y <= ey; ++y) {
		x = k * y + b;
		if ((x - (int)x) > 0.5) {
			x += 1;
		}
		show_point(x, y, c);
	}

	return ;
}

//在屏幕上显示一条斜线
void draw_line_point(point s, point e, col c)
{
	draw_line(s.x, s.y, e.x, e.y, c);

	return ;
}

//绘制矩形
void draw_rect(int x0, int y0, int width, int height, col c)
{
	draw_h_line(x0, y0, width, c);
	draw_h_line(x0, y0 + height, width, c);
	draw_s_line(x0, y0, height, c);
	draw_s_line(x0 + width, y0, height, c);

	return ;
}

//填充矩形
void fill_rect(int x0, int y0, int width, int height, col c)
{
	int i;
	if (c.l == RGB_WITHE) {
		return ;
	}
	for (i = 0; i < height; ++i) {
		draw_h_line(x0, y0 + i, width, c);
	}

	return ;
}

//清屏
void clr_src(col c)
{
	fill_rect(0, 0, vinfo.xres, vinfo.yres, c);

	return ;
}

//连接N个点
void poly_line(point *pt, int n, col c)
{
	int i;
	for (i = 0; i < n; ++i) {
		draw_line_point(pt[i], pt[i+1], c);
	}

	return ;
}

//圆形，几何多边形，圆心，边数量
void draw_circle_n(point pt0, int r, int n, col c)
{
	point *pt = malloc(sizeof(point) * (n + 1)); //按照圆计算定点坐标

	int i;
	for (i = 0; i < n; ++i) {
		pt[i].x = r * cos(2 * PI * i / n) + pt0.x;
		pt[i].y = r * sin(2 * PI * i / n) + pt0.y;
	}

	pt[n].x = pt[0].x;
	pt[n].y = pt[0].y;

	poly_line(pt, n + 1, c);

	free(pt);
	pt = NULL;

	return ;
}

//ascii文字
void draw_a_ascii_by_zimo(int x0, int y0, unsigned char *zimo, col f, col bk)
{
	int x, y;

	for (y = 0; y < 16; ++y) {
		unsigned char tmp = *zimo++;
		for (x = 0; x < 8; ++x) {
			if (tmp & 0x80) {
				show_point(x0 + x, y0 + y, f);
			} else {
				if (bk.l != RGB_TRANS) {
					show_point(x0 + x, y0 + y, bk);
				}
			}
			tmp = tmp << 1;
		}
	}

	return ;
}

unsigned char font_8x16[4096];
void draw_a_ascii(int x0, int y0, char ch, col f, col bk)
{	
	unsigned char *pzimo = (void *)(font_8x16 + (int)ch * 16UL);
	draw_a_ascii_by_zimo(x0, y0, pzimo, f, bk);

	return ;
}

void draw_string(int x0, int y0, char *str, col f, col bk)
{
	int len = strlen(str);
	int i;

	for (i = 0; i < len; ++i) {
		switch (*str) {
		case '\r': 
			x0 = 0;
			break;
		case '\n': 
			x0 = 0;
			y0 += 16;
			break;
		case '\t':
			break;
		case '\b':
			break;
		default:
			draw_a_ascii(x0, y0, *str, f, bk);
			x0 += 8;
			str++;
			break;
		}
	}

	return ;
}

//中文
void draw_a_chinese_by_zimo(int x0, int y0, unsigned char *zimo, col f, col bk)
{
	int x, y;

	for (y = 0; y < 16; ++y) {
		unsigned short tmp = *zimo++;
		tmp = tmp << 8;
		tmp |= *zimo++;

		for (x = 0; x < 16; ++x) {
			if (tmp & 0x8000) {
				show_point(x0 + x, y0 + y, f);
			} else {
				show_point(x0 + x, y0 + y, bk);
			}
			tmp = tmp << 1;
		}
	}

	return ;
}

void draw_a_chinese(int x0, int y0, unsigned char code[2], col f, col bk)
{
	//STEP 1,根据汉字编码计算字库偏移
	long offset = (code[0] - 0xa1UL) * 94 + (code[1] - 0xa1);
	offset = offset * 32; //用的字库是16*16，每个字模占32字节

	unsigned char zimo[32];
	int fd_gb2312 = open("./res/gb2312.dat", O_RDONLY);
	if (-1 == fd_gb2312) {
		perror("gb2312 open err");
		exit(EXIT_FAILURE);
	}
	lseek(fd_gb2312, offset, SEEK_SET);
	read(fd_gb2312, zimo, sizeof(zimo));

	draw_a_chinese_by_zimo(x0, y0, zimo, f, bk);

	close(fd_gb2312);

	return ;
}

//显示汉字
void draw_chinese(int x0, int y0, unsigned char *str, col f, col bk)
{
	int len = strlen(str);
	int i;

	for (i = 0; i < len / 2; ++i) {
		draw_a_chinese(x0, y0, str, f, bk);
		x0 += 16;
		str += 2;
	}

	return ;
}

//统一汉字和ASCII的显示
void draw_text(int x0, int y0, unsigned char *str, col f, col bk)
{
	while (*str != '\0') {
		if (*str < 128) {
			switch (*str) {
			case '\r':
				x0 = 0;
				break;
			case '\n':
				y0 += 20; 
				x0 = 0;
				break;
			default:
				draw_a_ascii(x0, y0, *str, f, bk);
				x0 += 8;
				break;
			}
			str++;
		} else {
			draw_a_chinese(x0, y0, str, f, bk);
			x0 += 16;
			str += 2;
		}
	}

	
	return ;
}

//最大显示n个字符
void draw_text_n(int x0, int y0, unsigned char *str, int n, col f, col bk)
{
	int i = 0;
	while ((str[i] != '\0') && (i < n)) {
		if (str[i] < 128) {
			switch (str[i]) {
			case '\r': 
				x0 = 0;
				break;
			case '\n':
				y0 += 20;
				x0 = 0;
				break;
			default:
				draw_a_ascii(x0, y0, str[i], f, bk);
				x0 += 8;
				break;
			}
			i++;
		} else {
			draw_a_chinese(x0, y0, str + i, f, bk);
			x0 += 16;
			i += 2;
		}
			
	}

	return ;
}

//图片显示模块
tag_bmp *load_bmp(char *filename)
{
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;

	//打开位图
	int bmp_fd = open(filename, O_RDONLY);
	if (-1 == bmp_fd) {
		perror("open bmp err!");
		return ;
	}

	read (bmp_fd, &head, sizeof(head)); //读取图片文件头信息
	read (bmp_fd, &info, sizeof(info)); //读图片图像信息

	tag_bmp *p = malloc(sizeof(tag_bmp));
	p->width = info.biWidth;
	p->height = info.biHeight;
	p->data = malloc (p->width * p->height * 3); //分配数据空间
	read (bmp_fd, p->data, info.biWidth * info.biHeight *3);

	close (bmp_fd);

	return p;
}

//将加载的图片显示在屏幕上
void show_bmp (int x0, int y0, tag_bmp *p)
{
	int i, j;

	unsigned char *pdata = p->data;
	for (j = 0; j < p->height; ++j) {
		for (i = 0; i < p->width; ++i) {
			col c;
			c.rgb.b = *pdata++;
			c.rgb.g = *pdata++;
			c.rgb.r = *pdata++;
			show_point(x0 + i, p->height - j + y0, c);
		}
	}

	return ;
}

void show_bmp_reverse(int x0, int y0, tag_bmp *p)
{
	int i, j;

	unsigned char *pdata = p->data;
	for (j = 0; j < p->height; ++j) {
		for (i = 0; i < p->width; ++i) {
//一次取一个点
#if COL_DEPTH==24
			col c;
			c.rgb.b = *pdata++;
			c.rgb.g = *pdata++;
			c.rgb.r = *pdata++;
#else
			col c;
			unsigned int r, g, b;
			b = *pdata++;
			g = *pdata++;
			r = *pdata++;
			c.l = (b >> 3) | ((g >> 2) << 5) | ((r >> 3) << 11);
#endif
			show_point(x0 + i, y0 + j, c);
		}
	}

	return;
}

//将加载的图片显示在屏幕上
void show_cursor(int x0, int y0, tag_bmp *p)
{
	int i, j;

	unsigned char *pdata = p->data;
	for (j = 0; j < p->height; ++j) {
		for (i = 0; i < p->width; ++i) {
			col c;
			c.rgb.b = *pdata++;
			c.rgb.g = *pdata++;
			c.rgb.r = *pdata++;
			if (c.l != RGB_WITHE) {
				show_point(x0 + i, p->height -j + y0, c);
			}
		}
	}

	return ;
}

//释放图片资源
void free_bmp(tag_bmp *p) 
{
	free (p->data);
	free (p);
	
	return ;
}

//显示图标
//绘制图标
void draw_icon (icon *m_icon)
{
	if (m_icon->bk.l != RGB_TRANS) {
		fill_rect (m_icon->m_rect.x,
				   m_icon->m_rect.y,
				   m_icon->m_rect.w,
				   m_icon->m_rect.h,
				   m_icon->bk);
	}

	int x, y, w, h;
	w = (m_icon->m_rect.w - m_icon->pbmp->width) / 2;
	x = m_icon->m_rect.x + w;

	h = (m_icon->m_rect.h - m_icon->pbmp->height - FONT_HEIGHT) / 2;
	y = m_icon->m_rect.y + h;

	//显示图片
	show_bmp(x, y, m_icon->pbmp);
	
	//先计算下矩形区域内
	//单行能够显示的最大数量，矩形的左右都预留两个像素，因此减去4
	//int len = (m_icon->m_rect.w -4) / FONT_WIDTH_PER_BYTE;
	
	//计算字显示的起始坐标
	int len = strlen(m_icon->name) * 8;
	if (len > m_icon->pbmp->width - 4) {
		len = m_icon->pbmp->width - 4;
	}

	x = m_icon->m_rect.x + 2 + (m_icon->m_rect.w - len) / 2;
	y = m_icon->m_rect.y + h + m_icon->pbmp->height + 2;
	len = len / FONT_WIDTH_PER_BYTE;
	draw_text_n(x, y, m_icon->name, len, m_icon->f, m_icon->bk);

	return ;
}

//创建图标
icon *create_icon(rect m_rect, tag_bmp *p, char *name, col f, col bk, int type)
{
	icon *new = malloc(sizeof(icon));
	if (!new) {
		return NULL;
	}
	
	new->select = 0;
	new->type = type;
	new->m_rect = m_rect;
	new->pbmp = p;
	strcpy (new->name, name);
	new->f = f;
	new->bk = bk;

	return new;
}
