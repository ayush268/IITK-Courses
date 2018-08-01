all: exe lib


exe:cs251.ex1
lib:cs251.a

CC=gcc
CFLAGS= -g -I. -DDBG
MAKELIB=ar
RANLIB=ranlib

mainobj=main.o
SOURCES = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SOURCES))
LIBOBJS = $(filter-out $(mainobj),$(OBJS))

cs251.ex1:$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS) : common.h
graphics.o : math.o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

cs251.a:$(LIBOBJS)
	$(MAKELIB) rc $@ $(LIBOBJS)
	$(RANLIB) $@

clean:
	rm -f *.o cs251.ex1 cs251.a
	
