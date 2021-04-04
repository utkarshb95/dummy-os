gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot1.o boot1.S
gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot1main.o boot1main.c
gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot1lib.o boot1lib.c
gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o exec_kernel.o exec_kernel.S
ld -nostdlib -m elf_i386 -N -e start -Ttext 0x7e00 -o boot1.elf boot1.o boot1main.o boot1lib.o exec_kernel.o
objcopy -S -O binary boot1.elf boot1