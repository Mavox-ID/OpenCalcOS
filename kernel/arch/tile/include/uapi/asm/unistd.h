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
#if !defined(__LP64__) || defined(__SYSCALL_COMPAT)
/* Use the flavor of this syscall that matches the 32-bit API better. */
#define __ARCH_WANT_SYNC_FILE_RANGE2
#endif

/* Use the standard ABI for syscalls. */
#include <asm-generic/unistd.h>

/* Additional Tilera-specific syscalls. */
#define __NR_cacheflush	(__NR_arch_specific_syscall + 1)
__SYSCALL(__NR_cacheflush, sys_cacheflush)

#ifndef __tilegx__
/* "Fast" syscalls provide atomic support for 32-bit chips. */
#define __NR_FAST_cmpxchg	-1
#define __NR_FAST_atomic_update	-2
#define __NR_FAST_cmpxchg64	-3
#define __NR_cmpxchg_badaddr	(__NR_arch_specific_syscall + 0)
__SYSCALL(__NR_cmpxchg_badaddr, sys_cmpxchg_badaddr)
#endif
