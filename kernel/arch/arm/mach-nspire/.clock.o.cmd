cmd_arch/arm/mach-nspire/clock.o := arm-none-eabi-gcc -Wp,-MD,arch/arm/mach-nspire/.clock.o.d -nostdinc -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/install/lib/gcc/arm-none-eabi/14.2.0/include -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi -Iinclude/generated/uapi -include /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/beep/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-nspire/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork -marm -D__BEEP_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -w    -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(clock)"  -D"KBUILD_MODNAME=KBUILD_STR(clock)" -c -o arch/arm/mach-nspire/clock.o arch/arm/mach-nspire/clock.c

source_arch/arm/mach-nspire/clock.o := arch/arm/mach-nspire/clock.c

deps_arch/arm/mach-nspire/clock.o := \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/errno-base.h \
  arch/arm/mach-nspire/include/mach/clkdev.h \

arch/arm/mach-nspire/clock.o: $(deps_arch/arm/mach-nspire/clock.o)

$(deps_arch/arm/mach-nspire/clock.o):
