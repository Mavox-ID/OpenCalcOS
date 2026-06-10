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
#ifndef _ASM_MICROBLAZE_FLAT_H
#define _ASM_MICROBLAZE_FLAT_H

#include <asm/unaligned.h>

#define	flat_argvp_envp_on_stack()	0
#define	flat_old_ram_flag(flags)	(flags)
#define	flat_reloc_valid(reloc, size)	((reloc) <= (size))
#define	flat_set_persistent(relval, p)		0

/*
 * Microblaze works a little differently from other arches, because
 * of the MICROBLAZE_64 reloc type. Here, a 32 bit address is split
 * over two instructions, an 'imm' instruction which provides the top
 * 16 bits, then the instruction "proper" which provides the low 16
 * bits.
 */

/*
 * Crack open a symbol reference and extract the address to be
 * relocated. rp is a potentially unaligned pointer to the
 * reference
 */

static inline unsigned long
flat_get_addr_from_rp(unsigned long *rp, unsigned long relval,
			unsigned long flags, unsigned long *persistent)
{
	unsigned long addr;
	(void)flags;

	/* Is it a split 64/32 reference? */
	if (relval & 0x80000000) {
		/* Grab the two halves of the reference */
		unsigned long val_hi, val_lo;

		val_hi = get_unaligned(rp);
		val_lo = get_unaligned(rp+1);

		/* Crack the address out */
		addr = ((val_hi & 0xffff) << 16) + (val_lo & 0xffff);
	} else {
		/* Get the address straight out */
		addr = get_unaligned(rp);
	}

	return addr;
}

/*
 * Insert an address into the symbol reference at rp. rp is potentially
 * unaligned.
 */

static inline void
flat_put_addr_at_rp(unsigned long *rp, unsigned long addr, unsigned long relval)
{
	/* Is this a split 64/32 reloc? */
	if (relval & 0x80000000) {
		/* Get the two "halves" */
		unsigned long val_hi = get_unaligned(rp);
		unsigned long val_lo = get_unaligned(rp + 1);

		/* insert the address */
		val_hi = (val_hi & 0xffff0000) | addr >> 16;
		val_lo = (val_lo & 0xffff0000) | (addr & 0xffff);

		/* store the two halves back into memory */
		put_unaligned(val_hi, rp);
		put_unaligned(val_lo, rp+1);
	} else {
		/* Put it straight in, no messing around */
		put_unaligned(addr, rp);
	}
}

#define	flat_get_relocate_addr(rel)	(rel & 0x7fffffff)

#endif /* _ASM_MICROBLAZE_FLAT_H */
