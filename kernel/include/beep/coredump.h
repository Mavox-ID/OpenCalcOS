#ifndef _BEEP_COREDUMP_H
#define _BEEP_COREDUMP_H

#include <beep/types.h>
#include <beep/mm.h>
#include <beep/fs.h>
#include <asm/siginfo.h>

/*
 * These are the only things you should do on a core-file: use only these
 * functions to write out all the necessary info.
 */
extern int dump_write(struct file *file, const void *addr, int nr);
extern int dump_seek(struct file *file, loff_t off);
#ifdef CONFIG_COREDUMP
extern void do_coredump(siginfo_t *siginfo);
#else
static inline void do_coredump(siginfo_t *siginfo) {}
#endif

#endif /* _BEEP_COREDUMP_H */
