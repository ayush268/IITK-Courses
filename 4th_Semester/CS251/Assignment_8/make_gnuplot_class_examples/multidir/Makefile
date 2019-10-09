all: exe lib


exe:cs251.ex1
lib:cs251.a

MAKELIB=ar
RANLIB=ranlib


include Makefile.defs

CFLAGS += -I include

SUBDIRS := gpu io math 

$(SUBDIRS):
	$(MAKE) -C $@


SOURCES = $(wildcard *.c)
THISOBJS = $(patsubst %.c, %.o, $(SOURCES))

OBJS = $(shell find $(CURDIR) -type f -name '*.o')
LIBOBJS = $(filter-out $(THISOBJS),$(OBJS))

$(THISOBJS) : $(INCLUDE/common.h)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

cs251.ex1:$(SUBDIRS) $(THISOBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


cs251.a:$(SUBDIRS)
	$(MAKELIB) rc $@ $(LIBOBJS)
	$(RANLIB) $@

.PHONY: $(SUBDIRS) clean all exe lib
clean:
	rm -f gpu/*.o io/*.o math/*.o *.o cs251.ex1 cs251.a 
	
