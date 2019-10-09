all: gemOS.kernel
SRCS = main.c lib.c idt.c kbd.c shell.c serial.c memory.c userapp.c contect.c context_mm.c
OBJS = boot.o main.o lib.o idt.o kbd.o shell.o serial.o memory.o userapp.o context.o context_mm.o
CFLAGS  = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -fpic -m64 -I./include
LDFLAGS = -nostdlib -nodefaultlibs  -q -melf_x86_64 -Tlink64.ld 
ASFLAGS = --64  
AS = as 


%o: %c
	gcc -c $(CFLAGS) $< -o $@ 

#boot.o : boot_64.S
#	$(AS) $(ASFLAGS) $^ -o $@

gemOS.kernel: $(OBJS)
	ld $(LDFLAGS) -o $@ $(OBJS)

.Phony: clean
clean:
	rm -f gemOS.kernel
