#ifndef __ASM_SH_SYSCALLS_64_H
#define __ASM_SH_SYSCALLS_64_H

#ifdef __KERNEL__

#include <beep/compiler.h>
#include <beep/linkage.h>
#include <beep/types.h>

struct pt_regs;

/* Misc syscall related bits */
asmlinkage long long do_syscall_trace_enter(struct pt_regs *regs);
asmlinkage void do_syscall_trace_leave(struct pt_regs *regs);

#endif /* __KERNEL__ */
#endif /* __ASM_SH_SYSCALLS_64_H */
