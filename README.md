# dummy-os
A dummy OS to demonstrate working of bootloader and kernel.

## Building boot0: Compilation
```
$ gcc​ -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot0.o boot0.S
```
The GNU compiler collection, gcc command, compiles the assembly code into object code. Please note that no standard
C libraries are included here, which means you cannot use functions like printf().

## Building boot0: Linking
```
$ ​ld -nostdlib -m elf_i386 -N -e start -Ttext 0x7c00 -o boot0.elf boot0.o
```
