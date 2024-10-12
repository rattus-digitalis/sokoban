CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o

all: sokoban

sokoban: $(OBJS)
	$(CC) -o sokoban $(OBJS)

main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) sokoban
