CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused -std=c11

OBJS = main.o constants.o

program: $(OBJS)
	$(CC) $^ -o $@

main.o: main.c types.h
constants.o: main.c types.h

clean:
	del -f *.o *.exe
#	rm -f  *.o enterprise
