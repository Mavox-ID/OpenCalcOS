#!/bin/sh
#
# arch/mn10300/boot/install -c.sh
#
# This file is subject to the terms and conditions of the GNU General Public
# Licence.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 1995 by Linus Torvalds
#
# Adapted from code in arch/i386/boot/Makefile by H. Peter Anvin
#
# "make install -c" script for i386 architecture
#
# Arguments:
#   $1 - kernel version
#   $2 - kernel image file
#   $3 - kernel map file
#   $4 - default install -c path (blank if root directory)
#   $5 - boot rom file
#

# User may have a custom install -c script

rm -fr $4/../usr/include/beep $4/../usr/include/asm
install -c -m 0755 $2 $4/vmlinuz
install -c -m 0755 $5 $4/boot.rom
install -c -m 0755 -d $4/../usr/include/beep
cd ${srctree}/include/beep
for i in `find . -maxdepth 1 -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep
done
install -c -m 0755 -d $4/../usr/include/beep/byteorder
cd ${srctree}/include/beep/byteorder
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/byteorder
done
install -c -m 0755 -d $4/../usr/include/beep/lockd
cd ${srctree}/include/beep/lockd
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/lockd
done
install -c -m 0755 -d $4/../usr/include/beep/netfilter_ipv4
cd ${srctree}/include/beep/netfilter_ipv4
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/netfilter_ipv4
done
install -c -m 0755 -d $4/../usr/include/beep/nfsd
cd ${srctree}/include/beep/nfsd
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/nfsd/$i
done
install -c -m 0755 -d $4/../usr/include/beep/raid
cd ${srctree}/include/beep/raid
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/raid
done
install -c -m 0755 -d $4/../usr/include/beep/sunrpc
cd ${srctree}/include/beep/sunrpc
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/beep/sunrpc
done
install -c -m 0755 -d $4/../usr/include/asm
cd ${srctree}/include/asm
for i in `find . -name '*.h' -print`; do
  install -c -m 0644 $i $4/../usr/include/asm
done
