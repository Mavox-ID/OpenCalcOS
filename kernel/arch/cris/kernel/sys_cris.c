/* $Id: sys_cris.c,v 1.6 2004/03/11 11:38:40 starvik Exp $
 *
 * beep/arch/cris/kernel/sys_cris.c
 *
 * This file contains various random system calls that
 * have a non-standard calling sequence on some platforms.
 * Since we don't have to do any backwards compatibility, our
 * versions are done in the most "normal" way possible.
 *
 */

#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/syscalls.h>
#include <beep/mm.h>
#include <beep/fs.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/ipc.h>

#include <asm/uaccess.h>
#include <asm/segment.h>

asmlinkage long
sys_mmap2(unsigned long addr, unsigned long len, unsigned long prot,
          unsigned long flags, unsigned long fd, unsigned long pgoff)
{
	/* bug(?): 8Kb pages here */
        return sys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
}
