#include "show.h"
#include "log_in.h"
#include "input.h"

int main(void)
{
	screen_info s_info;

	fb_init(&s_info);
	input_init();

	tag_bmp *pbmp;
	pbmp = load_bmp("./interface/init.bmp");
	show_bmp(0, 0, pbmp);
	free_bmp(pbmp);

	while (1) {
		log_in();
	}

	return 0;
}

