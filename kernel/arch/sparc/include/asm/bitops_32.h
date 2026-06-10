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
#ifndef _SPARC_BITOPS_H
#define _SPARC_BITOPS_H

#include <beep/compiler.h>
#include <asm/byteorder.h>

#ifdef __KERNEL__

#ifndef _BEEP_BITOPS_H
#error only <beep/bitops.h> can be included directly
#endif

extern unsigned long ___set_bit(unsigned long *addr, unsigned long mask);
extern unsigned long ___clear_bit(unsigned long *addr, unsigned long mask);
extern unsigned long ___change_bit(unsigned long *addr, unsigned long mask);

/*
 * Set bit 'nr' in 32-bit quantity at address 'addr' where bit '0'
 * is in the highest of the four bytes and bit '31' is the high bit
 * within the first byte. Sparc is BIG-Endian. Unless noted otherwise
 * all bit-ops return 0 if bit was previously clear and != 0 otherwise.
 */
static inline int test_and_set_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	return ___set_bit(ADDR, mask) != 0;
}

static inline void set_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(void) ___set_bit(ADDR, mask);
}

static inline int test_and_clear_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	return ___clear_bit(ADDR, mask) != 0;
}

static inline void clear_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(void) ___clear_bit(ADDR, mask);
}

static inline int test_and_change_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	return ___change_bit(ADDR, mask) != 0;
}

static inline void change_bit(unsigned long nr, volatile unsigned long *addr)
{
	unsigned long *ADDR, mask;

	ADDR = ((unsigned long *) addr) + (nr >> 5);
	mask = 1 << (nr & 31);

	(void) ___change_bit(ADDR, mask);
}

#include <asm-generic/bitops/non-atomic.h>

#define smp_mb__before_clear_bit()	do { } while(0)
#define smp_mb__after_clear_bit()	do { } while(0)

#include <asm-generic/bitops/ffz.h>
#include <asm-generic/bitops/__ffs.h>
#include <asm-generic/bitops/sched.h>
#include <asm-generic/bitops/ffs.h>
#include <asm-generic/bitops/fls.h>
#include <asm-generic/bitops/__fls.h>
#include <asm-generic/bitops/fls64.h>
#include <asm-generic/bitops/hweight.h>
#include <asm-generic/bitops/lock.h>
#include <asm-generic/bitops/find.h>
#include <asm-generic/bitops/le.h>
#include <asm-generic/bitops/ext2-atomic.h>

#endif /* __KERNEL__ */

#endif /* defined(_SPARC_BITOPS_H) */
