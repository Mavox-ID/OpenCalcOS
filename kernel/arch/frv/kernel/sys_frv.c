/* sys_frv.c: FRV arch-specific syscall wrappers
 *
 * Copyright (C) 2003-5 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 * - Derived from arch/m68k/kernel/sys_m68k.c
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/fs.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/syscalls.h>
#include <beep/ipc.h>

#include <asm/setup.h>
#include <asm/uaccess.h>

asmlinkage long sys_mmap2(unsigned long addr, unsigned long len,
			  unsigned long prot, unsigned long flags,
			  unsigned long fd, unsigned long pgoff)
{
	/* As with sparc32, make sure the shift for mmap2 is constant
	   (12), no matter what PAGE_SIZE we have.... */

	/* But unlike sparc32, don't just silently break if we're
	   trying to map something we can't */
	if (pgoff & ((1 << (PAGE_SHIFT - 12)) - 1))
		return -EINVAL;

	return sys_mmap_pgoff(addr, len, prot, flags, fd,
			      pgoff >> (PAGE_SHIFT - 12));
}
