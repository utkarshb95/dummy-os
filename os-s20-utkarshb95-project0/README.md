# os-s20: Project 0: Bootloader

## Building boot0: Compilation
```
$ gcc​ -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot0.o boot0.S
```
## Building boot0: Linking
```
$ ​ld -nostdlib -m elf_i386 -N -e start -Ttext 0x7c00 -o boot0.elf boot0.o
```
## Building boot0: Object Copying
```
$ objcopy -S -O binary boot0.elf boot0
```

## Building boot1: Compilation
Now, starting from the boot/boot1 folder, the following command will compile boot1.S
```
$ gcc -MD -fno-builtin -nostdinc -fno-stack-protector -Os -g -m32 -I. -c -o boot1.o
boot1.S
```

## Building boot1: Linking
```
$ ld -nostdlib -m elf_i386 -N -e start -Ttext <BOOT1 STARTS ADDRESS> -o boot1.elf
boot1.o boot1main.o boot1lib.o exec_kernel.o
```

## Building boot1: Object Copying
```
$ objcopy -S -O binary boot1.elf boot1
```

## Building kernel: Compilation
Now, starting from the kern/init folder, the following command will compile entry.S
```
$ gcc -MD -fno-builtin -nostdinc -fno-stack-protector -D_KERN_ -Ikern -Ikern/kern -I.
-m32 -O0 -c -o entry.o entry.S
```

## Building kernel: Linking
```
$ ld -o kernel -nostdlib -e start -m elf_i386 -Ttext=0x00100000 entry.o -b binary
```

## Building final image: Disk Creation
For this last step, use these commands in the project root directory.
```
$ dd if=/dev/zero of=project0.img bs=512 count=256
$ parted -s project0.img "mktable msdos mkpart primary 63s -1s set 1 boot on"
$ dd if=boot/boot0/boot0 of=project0.img bs=446 count=1 conv=notrunc
$ dd if=boot/boot1/boot1 of=project0.img bs=512 count=<NUMBER OF SECTORS TO WRITE>
seek=1 conv=notrunc
$ dd if=kern/init/kernel of=project0.img bs=512 seek=63 conv=notrunc
```

