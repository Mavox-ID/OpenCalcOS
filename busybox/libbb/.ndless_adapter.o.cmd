cmd_libbb/ndless_adapter.o := arm-beep-gnueabi-gcc -Wp,-MD,libbb/.ndless_adapter.o.d  -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG  -DBB_VER='"1.36.1"' -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -finline-limit=0 -fno-builtin-strlen -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Oz -Wno-strict-prototypes -Wno-unused-function -Wno-discarded-qualifiers -Wno-overflow -D__UCLIBC__ -D_GNU_SOURCE -D__beep__ -fno-PIE    -DKBUILD_BASENAME='"ndless_adapter"'  -DKBUILD_MODNAME='"ndless_adapter"' -c -o libbb/ndless_adapter.o libbb/ndless_adapter.c

deps_libbb/ndless_adapter.o := \
  libbb/ndless_adapter.c \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/stdc-predef.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/dirent.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features-time64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/wordsize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/timesize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/sys/cdefs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/long-double.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs-hard.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/typesizes.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/time64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/dirent.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/posix1_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/local_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/linux/limits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/pthread_stack_min-dynamic.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/stddef.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/dirent_ext.h \

libbb/ndless_adapter.o: $(deps_libbb/ndless_adapter.o)

$(deps_libbb/ndless_adapter.o):
