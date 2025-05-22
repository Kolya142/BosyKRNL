set -e

ARCH=i386
BITS=32

cd sys
python3 build.py $ARCH $BITS
cd ..

# nasm boot/$ARCH.s
# cat boot/$ARCH krnl > blob.bin

clang -m$BITS -target $ARCH lib/crt0.c -o lib/crt0.o -static -c -nostdlib
clang -m$BITS -target $ARCH sbin/init.c lib/crt0.o -o sbin/init -static -nostdlib

cp sbin/init iso/iso/init

cp krnl iso/iso/boot/grub/krnl

grub-mkrescue iso/iso -o iso/bootable.iso

qemu-system-i386 iso/bootable.iso -m 2048m
