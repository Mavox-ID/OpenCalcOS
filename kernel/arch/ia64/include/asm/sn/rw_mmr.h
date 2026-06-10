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
#ifndef _ASM_IA64_SN_RW_MMR_H
#define _ASM_IA64_SN_RW_MMR_H


/*
 * This file that access MMRs via uncached physical addresses.
 * 	pio_phys_read_mmr  - read an MMR
 * 	pio_phys_write_mmr - write an MMR
 * 	pio_atomic_phys_write_mmrs - atomically write 1 or 2 MMRs with psr.ic=0
 *		Second MMR will be skipped if address is NULL
 *
 * Addresses passed to these routines should be uncached physical addresses
 * ie., 0x80000....
 */


extern long pio_phys_read_mmr(volatile long *mmr); 
extern void pio_phys_write_mmr(volatile long *mmr, long val);
extern void pio_atomic_phys_write_mmrs(volatile long *mmr1, long val1, volatile long *mmr2, long val2); 

#endif /* _ASM_IA64_SN_RW_MMR_H */
