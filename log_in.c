#include "log_in.h"
#include "input.h"
#include "user_do.h"
#include "user_ad.h"
#include "key.h"
#include "show.h"

//重新输入
void anew_get(void)
{
	col f;
	col bk;
	
	f.rgb.b = 0xff;
	f.rgb.g = 0x00;
	f.rgb.r = 0x00;

	draw_string(30, 60, "resume load", f, bk);

	return ;
}

void log_in(void)
{
	char user[12];
	char password[12];
	struct input_event ev; 
	int x, y;
	int i;
	char pkey;
	char *p = NULL;

	tag_bmp *pbmp;
	pbmp = load_bmp("./interface/login.bmp");

	while (1) {
		show_bmp(0, 0, pbmp);

		get_event(&ev);
		if (ev.type == EV_ABS && ev.code == REL_X) {
			x = ev.value;
		}
		if (ev.type == EV_ABS && ev.code == REL_Y) {
			y = ev.value;
		}
		if (0) { //如果坐标在user的区域，弹出键盘，获取输入
			key_init();
			p = user;
			while (1) {
				pkey = key_get();
				if (pkey == '\0') {
					break;
				}
				*p = pkey;
				if (p < user + 10) {
					p++;
				}
			}
		}
		if (0) { //如果坐标在password的区域，弹出键盘，获取输入
			key_init();
			p = password;
			while (1) {
				pkey = key_get();
				if (pkey == '\0') {
					break;
				}
				*p = pkey;
				if (p < user + 10) {
					p++;
				}
			}
		}
		if (0) { //如果坐标在确认范围内，則判断是否正确
			i = judge(user, password);
			if (1 == i) { //普通用户
				user_do();
			}
			if (2 == i) { //管理员用户
				user_ad();
			}
			if (0 == i) { //输入错误
				anew_get();
				sleep(10);
			}
		}
		if (0) { //如果坐标在返回，則退出
 			break;
		}
	}

	free_bmp(pbmp);

	return ;
}
