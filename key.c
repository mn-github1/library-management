#include "key.h"
#include "show.h"
#include "input.h"

//初始化按键，显示在屏幕上
void key_init(void)
{
	tag_bmp *pbmp;
	pbmp = load_bmp("./interface/key.bmp");
	show_bmp(0, 100, pbmp);

	free_bmp(pbmp);

	return ;
}

//根据得到坐标判断案件，返回键值
char key_get(void)
{
	char ch;
	int x, y;
	struct input_event ev;

	get_event(&ev);
	if (ev.type == EV_ABS && ev.code == REL_X) {
		x = ev.value;
	}
	if (ev.type == EV_ABS && ev.code == REL_Y) {
		y = ev.value;
	}
	if (0) { //第一行坐标

	}
	if (0) { //第二行坐标

	}
	if (0) { //第三行坐标

	}
	if (0) { //第四行坐标

	}
	if (0) { //第五行坐标

	}

	return '\0';
}
