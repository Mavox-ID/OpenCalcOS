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
/* In compat mode, we use sys_llseek() for compat_sys_llseek(). */
#ifdef CONFIG_COMPAT
#define __ARCH_WANT_SYS_LLSEEK
#define __ARCH_WANT_COMPAT_SYS_SCHED_RR_GET_INTERVAL
#endif
#define __ARCH_WANT_SYS_NEWFSTATAT
#define __ARCH_WANT_SYS_CLONE
#include <uapi/asm/unistd.h>
