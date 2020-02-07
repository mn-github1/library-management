#include "input.h"

static int fd_input[3];

int get_event(struct input_event *pev)
{
	fd_set rfds;
	int i, max_fd, ret;

	//求最大的文件描述符，作为select循环结束的条件
	max_fd = MAX(MAX(fd_input[0], fd_input[1]), fd_input[2]);

	FD_ZERO(&rfds);
	for (i = 0; i < 3; ++i) {
		FD_SET(fd_input[i], &rfds);
	}
	ret = select(max_fd + 1, &rfds, NULL, NULL, NULL);
	if (-1 == ret) {
		perror("select error");
	}

	if (ret > 0) {
		for (i = 0; i < sizeof(fd_input) / sizeof(fd_input[0]); ++i) {
			if (FD_ISSET(fd_input[i], &rfds)) {
				read(fd_input[i], pev, sizeof(struct input_event));
				return i;
			}
		}
	}

	return -1;
}

int input_init(void) 
{
	char device_name[64] = {0};
	int i;

	for (i = 0; i < 3; ++i) {
		sprintf(device_name, "/dev/input/event%d", i);
		fd_input[i] = open(device_name, O_RDWR);
		if (-1 == fd_input[i]) {
			perror("open err");
			return -1;
		}
	}

	return 0;
}
