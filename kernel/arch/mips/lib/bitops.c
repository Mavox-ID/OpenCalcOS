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
#include <beep/bitops.h>
#include <beep/irqflags.h>
#include <beep/export.h>


/**
 * __mips_set_bit - Atomically set a bit in memory.  This is called by
 * set_bit() if it cannot find a faster solution.
 * @nr: the bit to set
 * @addr: the address to start counting from
 */
void __mips_set_bit(unsigned long nr, volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a |= mask;
	raw_local_irq_restore(flags);
}
EXPORT_SYMBOL(__mips_set_bit);


/**
 * __mips_clear_bit - Clears a bit in memory.  This is called by clear_bit() if
 * it cannot find a faster solution.
 * @nr: Bit to clear
 * @addr: Address to start counting from
 */
void __mips_clear_bit(unsigned long nr, volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a &= ~mask;
	raw_local_irq_restore(flags);
}
EXPORT_SYMBOL(__mips_clear_bit);


/**
 * __mips_change_bit - Toggle a bit in memory.  This is called by change_bit()
 * if it cannot find a faster solution.
 * @nr: Bit to change
 * @addr: Address to start counting from
 */
void __mips_change_bit(unsigned long nr, volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	*a ^= mask;
	raw_local_irq_restore(flags);
}
EXPORT_SYMBOL(__mips_change_bit);


/**
 * __mips_test_and_set_bit - Set a bit and return its old value.  This is
 * called by test_and_set_bit() if it cannot find a faster solution.
 * @nr: Bit to set
 * @addr: Address to count from
 */
int __mips_test_and_set_bit(unsigned long nr,
			    volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;
	unsigned long res;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a);
	*a |= mask;
	raw_local_irq_restore(flags);
	return res;
}
EXPORT_SYMBOL(__mips_test_and_set_bit);


/**
 * __mips_test_and_set_bit_lock - Set a bit and return its old value.  This is
 * called by test_and_set_bit_lock() if it cannot find a faster solution.
 * @nr: Bit to set
 * @addr: Address to count from
 */
int __mips_test_and_set_bit_lock(unsigned long nr,
				 volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;
	unsigned long res;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a);
	*a |= mask;
	raw_local_irq_restore(flags);
	return res;
}
EXPORT_SYMBOL(__mips_test_and_set_bit_lock);


/**
 * __mips_test_and_clear_bit - Clear a bit and return its old value.  This is
 * called by test_and_clear_bit() if it cannot find a faster solution.
 * @nr: Bit to clear
 * @addr: Address to count from
 */
int __mips_test_and_clear_bit(unsigned long nr, volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;
	unsigned long res;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a);
	*a &= ~mask;
	raw_local_irq_restore(flags);
	return res;
}
EXPORT_SYMBOL(__mips_test_and_clear_bit);


/**
 * __mips_test_and_change_bit - Change a bit and return its old value.  This is
 * called by test_and_change_bit() if it cannot find a faster solution.
 * @nr: Bit to change
 * @addr: Address to count from
 */
int __mips_test_and_change_bit(unsigned long nr, volatile unsigned long *addr)
{
	volatile unsigned long *a = addr;
	unsigned bit = nr & SZLONG_MASK;
	unsigned long mask;
	unsigned long flags;
	unsigned long res;

	a += nr >> SZLONG_LOG;
	mask = 1UL << bit;
	raw_local_irq_save(flags);
	res = (mask & *a);
	*a ^= mask;
	raw_local_irq_restore(flags);
	return res;
}
EXPORT_SYMBOL(__mips_test_and_change_bit);
