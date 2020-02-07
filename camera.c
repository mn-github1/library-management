#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include "show.h"

#define errmsg(msg) do{perror(msg); exit(EXIT_FAILURE);} while(0)

#define VIDEO_WIDTH 	640
#define VIDEO_HEIGHT 	480

unsigned char rgb[VIDEO_WIDTH * VIDEO_HEIGHT * 3];

struct buffer {
	void *start;
	unsigned int length;
};

void yuyv_to_rgb(struct buffer bb)
{
	int i;
	int y0, u0, y1, v0;
	int r, g, b;

	unsigned char *yuyv = bb.start;

	//保存原始yuyv数据
	//把yuyv转化为rgb数据
	for (i = 0; i < (VIDEO_WIDTH * VIDEO_HEIGHT / 2); ++i) {
		y0 = yuyv[(i << 2)];
		y1 = yuyv[(i << 2) + 2];
		u0 = yuyv[(i << 2) + 1];
		v0 = yuyv[(i << 2) + 3];
		//彩色显示
#if 1
		r = y0 + 1.4075 * (v0 - 128);
		g = y0 - 0.3455 * (u0 - 128) - 0.7169 * (v0 - 128);
		b = y0 + 1.779 * (u0 - 128);
#endif

#if 0
		//灰度显示
		if (y0 > 80) {
			y0 = 255;
		} else {
			y0 = 0;
		}
#endif

#if 0 
		r = y0;
		g = y0;
		b = y0;
#endif

		if (b > 255) b = 255;
		if (b < 0) b = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (r > 255) r = 255;
		if (r < 0) r = 0;
		rgb[i * 6 + 0] = b;
		rgb[i * 6 + 1] = g;
		rgb[i * 6 + 2] = r;

#if 1
		r = y1 + 1.4075 * (v0 - 128);
		g = y1 - 0.3455 * (u0 - 128) - 0.7169 * (v0 - 128);
		b = y1 + 1.779 * (u0 - 128);
#endif

#if 0
		if (y1 > 80) {
			y1 = 255;
		} else {
			y1 = 0;
		}
#endif 

#if 0
		r = y1;
		g = y1;
		b = y1;
#endif
		if (b > 255) b = 255;
		if (b < 0) b = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (r > 255) r = 255;
		if (r < 0) r = 0;

		rgb[i * 6 + 3] = b;
		rgb[i * 6 + 4] = g;
		rgb[i * 6 + 5] = r;
	}

	return ;
}
#ifndef OPJ_STATIC
#define OPJ_STATIC
#endif
#include <setjmp.h>
#include "jpeglib.h"


void decompress_jpeg(unsigned char *data, int size)
{
	if (0 == size) {
		return ;
	}

	struct jpeg_decompress_struct cinfo;

	JSAMPARRAY buffer;
	int row_stride;

#if 0
	if ((infile = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return ;
	}
#endif

#if 0
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return ;
	}
#endif

	struct jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, data, size);

	(void) jpeg_read_header(&cinfo, TRUE);

	(void) jpeg_start_decompress(&cinfo);

	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (* cinfo.mem->alloc_sarray)
			((j_common_ptr) &cinfo, JPOOL_IMAGE,row_stride, 1);

	int cnt = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		memcpy(rgb + cnt, *buffer, 640 * 3);
		cnt += 640 * 3;
	}

	(void) jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	return ;
}

tag_bmp show_camera_to_lcd(void)
{
	tag_bmp bmp;
	bmp.width = VIDEO_WIDTH;
	bmp.height = VIDEO_HEIGHT;
	bmp.data = rgb;
	show_bmp_reverse(80, 0, &bmp);

	return bmp;
}

void start_capture(int fd_video)
{
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (-1 == ioctl(fd_video, VIDIOC_STREAMON, &type)) {
		errmsg("start streamon");
	}

	return ;
}

int camera_init(void) 
{
	screen_info s_info;
	int fd_video;

	//打开摄像头设备
	fd_video = open("/dev/video15", O_RDWR | O_NONBLOCK);
	if (-1 == fd_video) {
		errmsg("open video");
	}

	//初始化framebuffer
	fb_init(&s_info);

#if 1
	//设置视频格式
	struct v4l2_format s_fmt;
	s_fmt.fmt.pix.width = VIDEO_WIDTH;
	s_fmt.fmt.pix.height = VIDEO_HEIGHT;
	s_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	s_fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	s_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fd_video, VIDIOC_S_FMT, &s_fmt)) {
		errmsg("set format");
	}
#endif

	struct v4l2_requestbuffers req;
	req.count = 1;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	ioctl(fd_video, VIDIOC_REQBUFS, &req);

	//缓冲区与应用程序关联，使用mmap将四个缓冲区映射到用户空间
	struct buffer buffers[4];
	unsigned int n_buffers;
	for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
		struct v4l2_buffer buf;
		memset(&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;
		if (-1 == ioctl(fd_video, VIDIOC_QUERYBUF, &buf)) {
			errmsg("query buffer");
		}

		buffers[n_buffers].length = buf.length;
		//通过mmap将驱动中的四个缓冲区地址获得
		buffers[n_buffers].start = mmap(NULL,
				buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd_video, buf.m.offset);
		if (MAP_FAILED == buffers[n_buffers].start) {
			errmsg("map shared");
		}
		
		//将刚刚处理完的缓冲重新入队列尾，这样可以循环采集
		if (ioctl(fd_video, VIDIOC_QBUF, &buf) < 0) {
			printf("VIDIOC_QBUF error");
		}
	}

	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fd_video, VIDIOC_STREAMON, &type)) {
		errmsg("err");
	}
	
	while (1) {
		struct v4l2_buffer buf;
		tag_bmp bmpbuf;
		memset(&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		//取出图像数据
		ioctl(fd_video, VIDIOC_DQBUF, &buf);

		decompress_jpeg(buffers[buf.index].start, buf.length);

		bmpbuf = show_camera_to_lcd();
		ioctl(fd_video, VIDIOC_QBUF, &buf);
	}

	return 0;
}

