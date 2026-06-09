/*
 *  beep/arch/arm/kernel/sys_arm.c
 *
 *  Copyright (C) People who wrote beep/arch/i386/kernel/sys_i386.c
 *  Copyright (C) 1995, 1996 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  This file contains various random system calls that
 *  have a non-standard calling sequence on the Beep/arm
 *  platform.
 */
#include <beep/export.h>
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/fs.h>
#include <beep/file.h>
#include <beep/ipc.h>
#include <beep/uaccess.h>
#include <beep/slab.h>

/*
 * Since loff_t is a 64 bit type we avoid a lot of ABI hassle
 * with a different argument ordering.
 */
asmlinkage long sys_arm_fadvise64_64(int fd, int advice,
				     loff_t offset, loff_t len)
{
	return sys_fadvise64_64(fd, offset, len, advice);
}
