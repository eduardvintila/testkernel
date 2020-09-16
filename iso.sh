#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/test.kernel isodir/boot/test.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "test" {
	multiboot /boot/test.kernel
}
EOF
grub-mkrescue -o test.iso isodir
