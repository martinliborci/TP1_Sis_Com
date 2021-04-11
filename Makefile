AS		:= nasm
ASFLAGS := -f elf
CFLAGS	:= -m32
LDFLAGS := -m32
CC		:= gcc
CXX		:= g++
CXXFLAGS := -m32
#TARGETS := 
#DEP := main.o

.PHONY: clean

%.o: %.asm
	$(AS) $(ASFLAGS) $< 

%.o: %.c
	$(CC) $(CFLAGS) $@ $^

main:

clean :
	rm -f *.o $(TARGETS)
