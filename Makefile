CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wno-unused -std=c11

OBJS = main.o constants.o display.o fileio.o list.o validate.o menu.o

program: $(OBJS)
	$(CC) $^ -o $@

main.o: main.c types.h list.h display.h fileio.h menu.h
constants.o: constants.c types.h
list.o: list.c types.h list.h
display.o: display.c types.h display.h
fileio.o: fileio.c types.h list.h validate.h fileio.h
validate.o: validate.c types.h validate.h
menu.o: menu.c types.h list.h display.h validate.h menu.h

clean:
	del -f *.o *.exe
#	rm -f  *.o enterprise
