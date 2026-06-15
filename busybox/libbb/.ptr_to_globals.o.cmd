cmd_libbb/ptr_to_globals.o := arm-beep-gnueabi-gcc -Wp,-MD,libbb/.ptr_to_globals.o.d  -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG  -DBB_VER='"1.36.1"' -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -finline-limit=0 -fno-builtin-strlen -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Oz -Wno-strict-prototypes -Wno-unused-function -Wno-discarded-qualifiers -Wno-overflow -D__UCLIBC__ -D_GNU_SOURCE -D__beep__ -fno-PIE    -DKBUILD_BASENAME='"ptr_to_globals"'  -DKBUILD_MODNAME='"ptr_to_globals"' -c -o libbb/ptr_to_globals.o libbb/ptr_to_globals.c

deps_libbb/ptr_to_globals.o := \
  libbb/ptr_to_globals.c \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/stdc-predef.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features-time64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/wordsize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/timesize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/sys/cdefs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/long-double.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs-hard.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/linux/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/asm/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/asm-generic/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/asm-generic/errno-base.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/types/error_t.h \

libbb/ptr_to_globals.o: $(deps_libbb/ptr_to_globals.o)

$(deps_libbb/ptr_to_globals.o):
