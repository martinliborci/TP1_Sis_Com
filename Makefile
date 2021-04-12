CC=gcc
CFLAGS=-I.
NASM= nasm -f elf32

ASM: 
	$(NASM) suma.asm
	$(NASM) resta.asm
	$(NASM) binarioADecimalASM.asm
	$(NASM) decimalABinarioASM.asm 
	$(CC) -o main -m32 main.c suma.o resta.o decimalABinarioASM.o binarioADecimalASM.o
clean:
	rm *.o
