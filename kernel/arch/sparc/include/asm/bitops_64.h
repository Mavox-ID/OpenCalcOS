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
#ifndef _SPARC64_BITOPS_H
#define _SPARC64_BITOPS_H

#ifndef _BEEP_BITOPS_H
#error only <beep/bitops.h> can be included directly
#endif

#include <beep/compiler.h>
#include <asm/byteorder.h>

extern int test_and_set_bit(unsigned long nr, volatile unsigned long *addr);
extern int test_and_clear_bit(unsigned long nr, volatile unsigned long *addr);
extern int test_and_change_bit(unsigned long nr, volatile unsigned long *addr);
extern void set_bit(unsigned long nr, volatile unsigned long *addr);
extern void clear_bit(unsigned long nr, volatile unsigned long *addr);
extern void change_bit(unsigned long nr, volatile unsigned long *addr);

#include <asm-generic/bitops/non-atomic.h>

#define smp_mb__before_clear_bit()	barrier()
#define smp_mb__after_clear_bit()	barrier()

#include <asm-generic/bitops/fls.h>
#include <asm-generic/bitops/__fls.h>
#include <asm-generic/bitops/fls64.h>

#ifdef __KERNEL__

extern int ffs(int x);
extern unsigned long __ffs(unsigned long);

#include <asm-generic/bitops/ffz.h>
#include <asm-generic/bitops/sched.h>

/*
 * hweightN: returns the hamming weight (i.e. the number
 * of bits set) of a N-bit word
 */

extern unsigned long __arch_hweight64(__u64 w);
extern unsigned int __arch_hweight32(unsigned int w);
extern unsigned int __arch_hweight16(unsigned int w);
extern unsigned int __arch_hweight8(unsigned int w);

#include <asm-generic/bitops/const_hweight.h>
#include <asm-generic/bitops/lock.h>
#endif /* __KERNEL__ */

#include <asm-generic/bitops/find.h>

#ifdef __KERNEL__

#include <asm-generic/bitops/le.h>

#include <asm-generic/bitops/ext2-atomic-setbit.h>

#endif /* __KERNEL__ */

#endif /* defined(_SPARC64_BITOPS_H) */
