all: gemOS.kernel
OBJS = boot.o main.o lib.o idt.o kbd.o shell.o serial.o memory.o context.o entry.o
CFLAGS  = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -fpic -m64 -I./include -I../include -g 
LDFLAGS = -nostdlib -nodefaultlibs  -q -melf_x86_64 -Tlink64.ld 
ASFLAGS = --64  
AS = as 


%o: %c
	gcc -c $(CFLAGS) $< -o $@ 

user/init.o:user/init.c
	gcc -c $(CFLAGS) user/init.c -o user/init.o
gemOS.kernel: $(OBJS) user/init.o
	ld $(LDFLAGS) -o $@ $(OBJS) user/init.o

.Phony: clean
clean:
	rm -f entry.o; rm -f user/init.o; rm -f gemOS.kernel;
