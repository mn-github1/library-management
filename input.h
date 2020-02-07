#ifndef __INPUT_H
#define __INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/select.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int get_event(struct input_event *pev);
int input_init(void);

#endif 
