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
#ifndef _ASM_IA64_SN_MSPEC_H
#define _ASM_IA64_SN_MSPEC_H

#define FETCHOP_VAR_SIZE 64 /* 64 byte per fetchop variable */

#define FETCHOP_LOAD		0
#define FETCHOP_INCREMENT	8
#define FETCHOP_DECREMENT	16
#define FETCHOP_CLEAR		24

#define FETCHOP_STORE		0
#define FETCHOP_AND		24
#define FETCHOP_OR		32

#define FETCHOP_CLEAR_CACHE	56

#define FETCHOP_LOAD_OP(addr, op) ( \
         *(volatile long *)((char*) (addr) + (op)))

#define FETCHOP_STORE_OP(addr, op, x) ( \
         *(volatile long *)((char*) (addr) + (op)) = (long) (x))

#ifdef __KERNEL__

/*
 * Each Atomic Memory Operation (amo, formerly known as fetchop)
 * variable is 64 bytes long.  The first 8 bytes are used.  The
 * remaining 56 bytes are unaddressable due to the operation taking
 * that portion of the address.
 *
 * NOTE: The amo structure _MUST_ be placed in either the first or second
 * half of the cache line.  The cache line _MUST NOT_ be used for anything
 * other than additional amo entries.  This is because there are two
 * addresses which reference the same physical cache line.  One will
 * be a cached entry with the memory type bits all set.  This address
 * may be loaded into processor cache.  The amo will be referenced
 * uncached via the memory special memory type.  If any portion of the
 * cached cache-line is modified, when that line is flushed, it will
 * overwrite the uncached value in physical memory and lead to
 * inconsistency.
 */
struct amo {
        u64 variable;
        u64 unused[7];
};


#endif /* __KERNEL__ */

#endif /* _ASM_IA64_SN_MSPEC_H */
