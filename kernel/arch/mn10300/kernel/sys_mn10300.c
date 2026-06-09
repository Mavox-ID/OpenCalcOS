/* MN10300 Weird system calls
 *
 * Copyright (C) 2007 Matsushita Electric Industrial Co., Ltd.
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/syscalls.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/tty.h>

#include <asm/uaccess.h>

asmlinkage long old_mmap(unsigned long addr, unsigned long len,
			 unsigned long prot, unsigned long flags,
			 unsigned long fd, unsigned long offset)
{
	if (offset & ~PAGE_MASK)
		return -EINVAL;
	return sys_mmap_pgoff(addr, len, prot, flags, fd, offset >> PAGE_SHIFT);
}
