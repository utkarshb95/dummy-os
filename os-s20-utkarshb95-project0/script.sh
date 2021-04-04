dd if=/dev/zero of=project0.img bs=512 count=256
parted -s project0.img "mktable msdos mkpart primary 63s -1s set 1 boot on"
dd if=boot/boot0/boot0 of=project0.img bs=446 count=1 conv=notrunc
dd if=boot/boot1/boot1 of=project0.img bs=512 count=62 seek=1 conv=notrunc
dd if=kern/init/kernel of=project0.img bs=512 seek=63 conv=notrunc