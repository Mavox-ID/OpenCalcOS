/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * Copyright (C) 2006 Atmark Techno, Inc.
 *	Yasushi SHOJI <yashi@atmark-techno.com>
 *	Tetsuya OHKAWA <tetsuya@atmark-techno.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <beep/errno.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/syscalls.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/mman.h>
#include <beep/sys.h>
#include <beep/ipc.h>
#include <beep/file.h>
#include <beep/module.h>
#include <beep/err.h>
#include <beep/fs.h>
#include <beep/semaphore.h>
#include <beep/uaccess.h>
#include <beep/unistd.h>
#include <beep/slab.h>

#include <asm/syscalls.h>

asmlinkage long sys_mmap(unsigned long addr, unsigned long len,
			unsigned long prot, unsigned long flags,
			unsigned long fd, off_t pgoff)
{
	if (pgoff & ~PAGE_MASK)
		return -EINVAL;

	return sys_mmap_pgoff(addr, len, prot, flags, fd, pgoff >> PAGE_SHIFT);
}
