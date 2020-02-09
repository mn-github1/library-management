#include "user_do.h"
#include "show.h"
#include "input.h"
#include "camera.h"

//座位预约
void seat_reservation(void)
{

	return ;
}

//图书查询
void book_search(void)
{

	return ;
}

//图书借阅
void book_borrow()
{

	return ;
}

void user_do(void) 
{
	tag_bmp *pbmp;
	struct input_event ev;
	int x, y;
	
	pbmp = load_bmp("./interface/user_do.bmp");

	while (1) {
		show_bmp(0, 0, pbmp);

		get_event(&ev);
		if (ev.type == EV_ABS && ev.code == REL_X) {
			x = ev.value;
		}
		if (ev.type == EV_ABS && ev.code == REL_Y) {
			y = ev.value;
		}
		if (0) { //如果坐标在作座位预约，进入作为预约界面
			seat_reservation();	
		}
		if (0) { //如果坐标在图书查询，进入图书查询界面
			book_search();
		}
		if (0) { //如果坐标在图书借阅，进入图书借阅界面
			book_borrow();
		}
		if (0) { //如果坐标在返回，則退出
 			break;
		}
	}

	free_bmp(pbmp);

	return ;
}
