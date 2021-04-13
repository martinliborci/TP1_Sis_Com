CC=gcc
CFLAGS=-I.
NASM= nasm -f elf32

ASM: 
	$(NASM) suma.asm
	$(NASM) resta.asm
	$(NASM) decimalABinarioASM.asm 
	$(CC) -o tp1 -m32 main.c suma.o resta.o decimalABinarioASM.o
clean:
	rm *.o 
