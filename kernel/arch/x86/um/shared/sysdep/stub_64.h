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
#ifndef __SYSDEP_STUB_H
#define __SYSDEP_STUB_H

#include <sysdep/ptrace_user.h>

#define STUB_SYSCALL_RET PT_INDEX(RAX)
#define STUB_MMAP_NR __NR_mmap
#define MMAP_OFFSET(o) (o)

#define __syscall_clobber "r11","rcx","memory"
#define __syscall "syscall"

static inline long stub_syscall0(long syscall)
{
	long ret;

	__asm__ volatile (__syscall
		: "=a" (ret)
		: "0" (syscall) : __syscall_clobber );

	return ret;
}

static inline long stub_syscall2(long syscall, long arg1, long arg2)
{
	long ret;

	__asm__ volatile (__syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2) : __syscall_clobber );

	return ret;
}

static inline long stub_syscall3(long syscall, long arg1, long arg2, long arg3)
{
	long ret;

	__asm__ volatile (__syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3)
		: __syscall_clobber );

	return ret;
}

static inline long stub_syscall4(long syscall, long arg1, long arg2, long arg3,
				 long arg4)
{
	long ret;

	__asm__ volatile ("movq %5,%%r10 ; " __syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3),
		  "g" (arg4)
		: __syscall_clobber, "r10" );

	return ret;
}

static inline long stub_syscall5(long syscall, long arg1, long arg2, long arg3,
				 long arg4, long arg5)
{
	long ret;

	__asm__ volatile ("movq %5,%%r10 ; movq %6,%%r8 ; " __syscall
		: "=a" (ret)
		: "0" (syscall), "D" (arg1), "S" (arg2), "d" (arg3),
		  "g" (arg4), "g" (arg5)
		: __syscall_clobber, "r10", "r8" );

	return ret;
}

static inline void trap_myself(void)
{
	__asm("int3");
}

static inline void remap_stack(long fd, unsigned long offset)
{
	__asm__ volatile ("movq %4,%%r10 ; movq %5,%%r8 ; "
			  "movq %6, %%r9; " __syscall "; movq %7, %%rbx ; "
			  "movq %%rax, (%%rbx)":
			  : "a" (STUB_MMAP_NR), "D" (STUB_DATA),
			    "S" (UM_KERN_PAGE_SIZE),
			    "d" (PROT_READ | PROT_WRITE),
                            "g" (MAP_FIXED | MAP_SHARED), "g" (fd),
			    "g" (offset),
			    "i" (&((struct stub_data *) STUB_DATA)->err)
			  : __syscall_clobber, "r10", "r8", "r9" );
}

#endif
