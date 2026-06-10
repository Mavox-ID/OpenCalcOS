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
#ifndef _ASM_S390_DIAG_H
#define _ASM_S390_DIAG_H

/*
 * Diagnose 10: Release page range
 */
static inline void diag10_range(unsigned long start_pfn, unsigned long num_pfn)
{
	unsigned long start_addr, end_addr;

	start_addr = start_pfn << PAGE_SHIFT;
	end_addr = (start_pfn + num_pfn - 1) << PAGE_SHIFT;

	asm volatile(
		"0:	diag	%0,%1,0x10\n"
		"1:\n"
		EX_TABLE(0b, 1b)
		EX_TABLE(1b, 1b)
		: : "a" (start_addr), "a" (end_addr));
}

/*
 * Diagnose 14: Input spool file manipulation
 */
extern int diag14(unsigned long rx, unsigned long ry1, unsigned long subcode);

/*
 * Diagnose 210: Get information about a virtual device
 */
struct diag210 {
	u16 vrdcdvno;	/* device number (input) */
	u16 vrdclen;	/* data block length (input) */
	u8 vrdcvcla;	/* virtual device class (output) */
	u8 vrdcvtyp;	/* virtual device type (output) */
	u8 vrdcvsta;	/* virtual device status (output) */
	u8 vrdcvfla;	/* virtual device flags (output) */
	u8 vrdcrccl;	/* real device class (output) */
	u8 vrdccrty;	/* real device type (output) */
	u8 vrdccrmd;	/* real device model (output) */
	u8 vrdccrft;	/* real device feature (output) */
} __attribute__((packed, aligned(4)));

extern int diag210(struct diag210 *addr);

#endif /* _ASM_S390_DIAG_H */
