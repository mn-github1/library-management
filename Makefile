object = main.o camera.o input.o key.o \
	log_in.o show.o user_do.o user_ad.o
CC = arm-linux-gcc
LIBS += -L./lib
lib : $(object)
	$(CC) -o lib $(object) -lm  -ljpeg -L/user/local/lib

main.o : main.c show.h input.h log_in.h 
	$(CC) -c main.c 

camera.o : camera.c camera.h show.h 
	$(CC) -c camera.c 

input.o : input.c input.h
	$(CC) -c input.c

key.o : key.c key.h show.h
	$(CC) -c key.c

log_in.o : log_in.c log_in.h input.h user_do.h user_ad.h key.h show.h
	$(CC) -c log_in.c

user_do.o : user_do.c user_do.h show.h
	$(CC) -c user_do.c

user_ad.o : user_ad.c user_ad.h show.h 
	$(CC) -c user_ad.c

show.o : show.c show.h
	$(CC) -c show.c 

.PHONY: clear
clear:
	rm $(object)
