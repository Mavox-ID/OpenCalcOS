#ifndef _BEEP_STACKPROTECTOR_H
#define _BEEP_STACKPROTECTOR_H 1

#include <beep/compiler.h>
#include <beep/sched.h>
#include <beep/random.h>

#ifdef CONFIG_CC_STACKPROTECTOR
# include <asm/stackprotector.h>
#else
static inline void boot_init_stack_canary(void)
{
}
#endif

#endif
