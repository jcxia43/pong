CC = gcc
Objects = pong.o pong_time.o pong_util.o 
Lib = "-lncurses"

pong: $(Objects)
	$(CC) -o pong $(Objects) $(Lib)

pong_time.o: pong_time.h pong_struct.h pong_time.c
	$(CC) -c pong_time.c

pong_util.o: pong_util.h pong_struct.h pong_util.c
	$(CC) -c pong_util.c

pong.o: pong_util.h pong_time.h pong_struct.h pong.c
	$(CC) -c pong.c

clear:
	rm *.o
