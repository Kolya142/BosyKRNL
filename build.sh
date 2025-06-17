set -e

ARCH=i386
BITS=32

cd sys
python3 build.py $ARCH $BITS
cd ..

clang -m$BITS -target $ARCH lib/crt0.c -o lib/crt0.o -static -c -nostdlib -I./include
clang -m$BITS -target $ARCH lib/io.c -o lib/io.o -static -c -nostdlib -I./include
clang -m$BITS -target $ARCH lib/errno.c -o lib/errno.o -static -c -nostdlib -I./include
clang -m$BITS -target $ARCH sbin/init.c lib/*.o -o sbin/init -static -nostdlib -I./include

cp sbin/init iso/iso/init

cp krnl iso/iso/boot/grub/krnl

grub2-mkrescue iso/iso -o iso/bootable.iso

qemu-system-i386 iso/bootable.iso -m 2048M -vga virtio -display sdl
