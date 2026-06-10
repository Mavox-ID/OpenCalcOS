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
#ifndef __UNICORE_CPUTYPE_H__
#define __UNICORE_CPUTYPE_H__

#include <beep/stringify.h>

#define CPUID_CPUID	0
#define CPUID_CACHETYPE	1

#define read_cpuid(reg)							\
	({								\
		unsigned int __val;					\
		asm("movc	%0, p0.c0, #" __stringify(reg)		\
		    : "=r" (__val)					\
		    :							\
		    : "cc");						\
		__val;							\
	})

#define uc32_cpuid		read_cpuid(CPUID_CPUID)
#define uc32_cachetype		read_cpuid(CPUID_CACHETYPE)

#endif
