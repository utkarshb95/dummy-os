gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot0.o boot0.S
ld -nostdlib -m elf_i386 -N -e start -Ttext 0x7c00 -o boot0.elf boot0.o
objcopy -S -O binary boot0.elf boot0