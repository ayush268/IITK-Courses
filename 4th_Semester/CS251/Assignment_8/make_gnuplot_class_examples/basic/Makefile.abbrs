all:cs251.ex1    
CC=gcc
CFLAGS= -g -I. -DDBG

OBJS = graphics.o math.o io.o main.o

cs251.ex1:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o:main.c common.h
	$(CC) $(CFLAGS) -c main.c -o main.o
graphics.o:graphics.c math.o common.h
	$(CC) $(CFLAGS) -c $< -o $@
math.o:math.c common.h
	$(CC) $(CFLAGS) -c math.c -o math.o
io.o:io.c common.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o cs251.ex1
	
