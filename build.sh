set -e

ARCH=i386
BITS=32

cd sys
python3 build.py $ARCH $BITS
cd ..

# nasm boot/$ARCH.s
# cat boot/$ARCH krnl > blob.bin

cp krnl iso/iso/boot/grub/krnl

grub-mkrescue iso/iso -o iso/bootable.iso

qemu-system-i386 iso/bootable.iso
