all:
		arm-linux-gcc -g  main.c show.c show.h log_in.c log_in.h camera.c camera.h -ljpeg -lm  -o text

.PHONY: clean
clean:
	rm test
