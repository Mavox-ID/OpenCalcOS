cmd_lib/decompress_unxz.o := arm-none-eabi-gcc -Wp,-MD,lib/.decompress_unxz.o.d -nostdinc -isystem /home/runner/work/OpenCalcOS/OpenCalcOS/ndless/ndless-sdk/toolchain/install/lib/gcc/arm-none-eabi/14.2.0/include -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi -Iinclude/generated/uapi -include /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/beep/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=apcs-gnu -mno-thumb-interwork -marm -D__BEEP_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -w    -D"KBUILD_STR(s)=#s" -D"KBUILD_BASENAME=KBUILD_STR(decompress_unxz)"  -D"KBUILD_MODNAME=KBUILD_STR(decompress_unxz)" -c -o lib/decompress_unxz.o lib/decompress_unxz.c

source_lib/decompress_unxz.o := lib/decompress_unxz.c

deps_lib/decompress_unxz.o := \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/arm.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/sparc.h) \
  include/beep/decompress/mm.h \
  include/beep/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/symbol/prefix.h) \
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
    $(wildcard include/config/modules.h) \
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
  include/beep/fs.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/beep/wait.h \
    $(wildcard include/config/lockdep.h) \
  include/beep/list.h \
    $(wildcard include/config/debug/list.h) \
  include/beep/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/const.h \
  include/beep/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  include/beep/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/beep/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/beep/bug.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/arm/thumbee.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/beep/stringify.h \
  include/beep/bottom_half.h \
  include/beep/spinlock_types.h \
  include/beep/spinlock_types_up.h \
  include/beep/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/beep/rwlock_types.h \
  include/beep/spinlock_up.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/hw_breakpoint.h \
  include/beep/rwlock.h \
  include/beep/spinlock_api_up.h \
  include/beep/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/atomic.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/atomic-long.h \
  include/asm-generic/atomic64.h \
  arch/arm/include/generated/asm/current.h \
  include/asm-generic/current.h \
  include/uapi/beep/wait.h \
  include/beep/kdev_t.h \
  include/uapi/beep/kdev_t.h \
  include/beep/dcache.h \
  include/beep/rculist.h \
  include/beep/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/preempt/rt.h) \
  include/beep/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/beep/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/beep/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/beep/bitmap.h \
  include/beep/seqlock.h \
  include/beep/completion.h \
  include/beep/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/beep/rcutiny.h \
  include/beep/rculist_bl.h \
  include/beep/list_bl.h \
  include/beep/bit_spinlock.h \
  include/beep/path.h \
  include/beep/stat.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/stat.h \
  include/uapi/beep/stat.h \
  include/beep/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/beep/math64.h \
  include/uapi/beep/time.h \
  include/beep/uidgid.h \
    $(wildcard include/config/uidgid/strict/type/checks.h) \
    $(wildcard include/config/user/ns.h) \
  include/beep/highuid.h \
  include/beep/radix-tree.h \
  include/beep/rbtree.h \
  include/beep/pid.h \
  include/beep/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/beep/capability.h \
  include/uapi/beep/capability.h \
  include/beep/semaphore.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/fiemap.h \
  include/beep/shrinker.h \
  include/beep/migrate_mode.h \
  include/beep/percpu-rwsem.h \
  include/beep/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/beep/rwsem-spinlock.h \
  include/beep/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/beep/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/beep/pfn.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/beep/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  include/beep/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  include/uapi/beep/fs.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/limits.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/uapi/asm-generic/ioctl.h \
  include/beep/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  include/beep/percpu_counter.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/dqblk_xfs.h \
  include/beep/dqblk_v1.h \
  include/beep/dqblk_v2.h \
  include/beep/dqblk_qtree.h \
  include/beep/projid.h \
  include/uapi/beep/quota.h \
  include/beep/nfs_fs_i.h \
  include/beep/fcntl.h \
  include/uapi/beep/fcntl.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/uapi/asm/fcntl.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/asm-generic/fcntl.h \
  include/beep/err.h \
  include/beep/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  include/beep/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/cma.h) \
  include/beep/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/beep/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/beep/nodemask.h \
    $(wildcard include/config/movable/node.h) \
  include/beep/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/glue.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/pgtable-2level-types.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
  include/beep/sizes.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/asm-generic/getorder.h \
  include/beep/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/beep/notifier.h \
  include/beep/srcu.h \
  include/beep/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/beep/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/beep/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/beep/jiffies.h \
  include/beep/timex.h \
  include/uapi/beep/timex.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/include/uapi/beep/param.h \
  arch/arm/include/generated/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/uapi/asm-generic/param.h \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/timex.h \
    $(wildcard include/config/arch/multiplatform.h) \
  include/beep/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/runner/work/OpenCalcOS/OpenCalcOS/kernel/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
  include/asm-generic/topology.h \
  include/beep/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  include/beep/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
    $(wildcard include/config/memcg/kmem.h) \
  include/beep/kobject.h \
  include/beep/sysfs.h \
  include/beep/kobject_ns.h \
  include/beep/kref.h \
  include/beep/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  include/beep/vmalloc.h \
  include/beep/xz.h \

lib/decompress_unxz.o: $(deps_lib/decompress_unxz.o)

$(deps_lib/decompress_unxz.o):
