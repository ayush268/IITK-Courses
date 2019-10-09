include ../Makefile.defs

CFLAGS += -I ../include
SOURCES = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SOURCES))

all:$(OBJS)


$(OBJS): $(INCLUDE/common.h)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o 
