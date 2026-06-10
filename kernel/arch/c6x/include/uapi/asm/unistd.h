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
#define __ARCH_WANT_SYS_CLONE

/* Use the standard ABI for syscalls. */
#include <asm-generic/unistd.h>

/* C6X-specific syscalls. */
#define __NR_cache_sync	(__NR_arch_specific_syscall + 0)
__SYSCALL(__NR_cache_sync, sys_cache_sync)
