/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __ASM_C6X_SYSCALLS_H
#define __ASM_C6X_SYSCALLS_H

#include <beep/compiler.h>
#include <beep/linkage.h>
#include <beep/types.h>

/* The array of function pointers for syscalls. */
extern void *sys_call_table[];

/* The following are trampolines in entry.S to handle 64-bit arguments */
extern long sys_pread_c6x(unsigned int fd, char __user *buf,
			  size_t count, off_t pos_low, off_t pos_high);
extern long sys_pwrite_c6x(unsigned int fd, const char __user *buf,
			   size_t count, off_t pos_low, off_t pos_high);
extern long sys_truncate64_c6x(const char __user *path,
			       off_t length_low, off_t length_high);
extern long sys_ftruncate64_c6x(unsigned int fd,
			       off_t length_low, off_t length_high);
extern long sys_fadvise64_c6x(int fd, u32 offset_lo, u32 offset_hi,
			      u32 len, int advice);
extern long sys_fadvise64_64_c6x(int fd, u32 offset_lo, u32 offset_hi,
				u32 len_lo, u32 len_hi, int advice);
extern long sys_fallocate_c6x(int fd, int mode,
			      u32 offset_lo, u32 offset_hi,
			      u32 len_lo, u32 len_hi);
extern int sys_cache_sync(unsigned long s, unsigned long e);

#include <asm-generic/syscalls.h>

#endif /* __ASM_C6X_SYSCALLS_H */
