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
#include <beep/delay.h>
#include <beep/io.h>
#include <beep/module.h>

#include <asm/checksum.h>
#include <asm/uaccess.h>

/*
 * GCC functions
 */
extern unsigned long long __avr32_lsl64(unsigned long long u, unsigned long b);
extern unsigned long long __avr32_lsr64(unsigned long long u, unsigned long b);
extern unsigned long long __avr32_asr64(unsigned long long u, unsigned long b);
EXPORT_SYMBOL(__avr32_lsl64);
EXPORT_SYMBOL(__avr32_lsr64);
EXPORT_SYMBOL(__avr32_asr64);

/*
 * String functions
 */
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(memcpy);

EXPORT_SYMBOL(clear_page);
EXPORT_SYMBOL(copy_page);

/*
 * Userspace access stuff.
 */
EXPORT_SYMBOL(copy_from_user);
EXPORT_SYMBOL(copy_to_user);
EXPORT_SYMBOL(__copy_user);
EXPORT_SYMBOL(strncpy_from_user);
EXPORT_SYMBOL(__strncpy_from_user);
EXPORT_SYMBOL(clear_user);
EXPORT_SYMBOL(__clear_user);
EXPORT_SYMBOL(strnlen_user);

EXPORT_SYMBOL(csum_partial);
EXPORT_SYMBOL(csum_partial_copy_generic);

/* Delay loops (lib/delay.S) */
EXPORT_SYMBOL(__ndelay);
EXPORT_SYMBOL(__udelay);
EXPORT_SYMBOL(__const_udelay);

/* Bit operations (lib/findbit.S) */
EXPORT_SYMBOL(find_first_zero_bit);
EXPORT_SYMBOL(find_next_zero_bit);
EXPORT_SYMBOL(find_first_bit);
EXPORT_SYMBOL(find_next_bit);
EXPORT_SYMBOL(find_next_bit_le);
EXPORT_SYMBOL(find_next_zero_bit_le);

/* I/O primitives (lib/io-*.S) */
EXPORT_SYMBOL(__raw_readsb);
EXPORT_SYMBOL(__raw_readsw);
EXPORT_SYMBOL(__raw_readsl);
EXPORT_SYMBOL(__raw_writesb);
EXPORT_SYMBOL(__raw_writesw);
EXPORT_SYMBOL(__raw_writesl);
