cmd_libbb/perror_nomsg.o := arm-beep-gnueabi-gcc -Wp,-MD,libbb/.perror_nomsg.o.d  -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG  -DBB_VER='"1.36.1"' -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include -w -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -finline-limit=0 -fno-builtin-strlen -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Oz -Wno-strict-prototypes -Wno-unused-function -Wno-discarded-qualifiers -Wno-overflow -D__UCLIBC__ -D_GNU_SOURCE -D__beep__ -fno-PIE    -DKBUILD_BASENAME='"perror_nomsg"'  -DKBUILD_MODNAME='"perror_nomsg"' -c -o libbb/perror_nomsg.o libbb/perror_nomsg.c

deps_libbb/perror_nomsg.o := \
  libbb/perror_nomsg.c \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/stdc-predef.h \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/nommu.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/limits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/syslimits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/limits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/libc-header-start.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/features-time64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/wordsize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/timesize.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/sys/cdefs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/long-double.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/gnu/stubs-hard.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/posix1_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/local_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/linux/limits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/pthread_stack_min-dynamic.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/posix2_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/xopen_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/uio_lim.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/stdint.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/stdint.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/typesizes.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/time64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/wchar.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/stdint-intn.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/stdint-uintn.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/stdint-least.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/stdbool.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/unistd.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/posix_opt.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/environments.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/lib/gcc/arm-none-linux-gnueabihf/14.2.1/include/stddef.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/confname.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/getopt_posix.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/getopt_core.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/archives/beep-toolchain/arm-none-linux-gnueabihf/libc/usr/include/bits/unistd_ext.h \

libbb/perror_nomsg.o: $(deps_libbb/perror_nomsg.o)

$(deps_libbb/perror_nomsg.o):
