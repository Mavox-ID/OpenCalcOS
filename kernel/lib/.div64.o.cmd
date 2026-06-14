cmd_lib/div64.o := arm-none-eabi-gcc -Wp,-MD,lib/.div64.o.d -nostdinc -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/install/lib/gcc/arm-none-eabi/14.2.0/include -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi -Iinclude/generated/uapi -include /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/beep/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork -marm -D__BEEP_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -w    -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(div64)"  -D"KBUILD_MODNAME=KBUILD_STR(div64)" -c -o lib/div64.o lib/div64.c

source_lib/div64.o := lib/div64.c

deps_lib/div64.o := \
  include/beep/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  include/beep/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/install/lib/gcc/arm-none-eabi/14.2.0/include/stdarg.h \
  include/beep/linkage.h \
  include/beep/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/beep/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/beep/compiler-gcc14.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/linkage.h \
  include/beep/stddef.h \
  include/uapi/beep/stddef.h \
  include/beep/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/beep/types.h \
  arch/arm/include/generated/asm/types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/posix_types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/posix_types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/posix_types.h \
  include/beep/bitops.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/beep/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/beep/typecheck.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/irqflags.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/hwcap.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/byteorder.h \
  include/beep/byteorder/little_endian.h \
  include/uapi/beep/byteorder/little_endian.h \
  include/beep/swab.h \
  include/uapi/beep/swab.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/swab.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/swab.h \
  include/beep/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/beep/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/beep/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/beep/init.h \
    $(wildcard include/config/broken/rodata.h) \
  include/beep/kern_levels.h \
  include/beep/dynamic_debug.h \
  include/beep/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/beep/string.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/string.h \
  include/beep/errno.h \
  include/uapi/beep/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/errno.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/errno-base.h \
  include/uapi/beep/kernel.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/sysinfo.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/div64.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/compiler.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  include/beep/math64.h \

lib/div64.o: $(deps_lib/div64.o)

$(deps_lib/div64.o):
