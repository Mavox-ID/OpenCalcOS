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
#ifndef __BLACKFIN_FLAT_H__
#define __BLACKFIN_FLAT_H__

#include <asm/unaligned.h>

#define	flat_argvp_envp_on_stack()		0
#define	flat_old_ram_flag(flags)		(flags)

extern unsigned long bfin_get_addr_from_rp (unsigned long *ptr,
					unsigned long relval,
					unsigned long flags,
					unsigned long *persistent);

extern void bfin_put_addr_at_rp(unsigned long *ptr, unsigned long addr,
		                unsigned long relval);

/* The amount by which a relocation can exceed the program image limits
   without being regarded as an error.  */

#define	flat_reloc_valid(reloc, size)	((reloc) <= (size))

#define	flat_get_addr_from_rp(rp, relval, flags, persistent)	\
	bfin_get_addr_from_rp(rp, relval, flags, persistent)
#define	flat_put_addr_at_rp(rp, val, relval)	\
	bfin_put_addr_at_rp(rp, val, relval)

/* Convert a relocation entry into an address.  */
static inline unsigned long
flat_get_relocate_addr (unsigned long relval)
{
	return relval & 0x03ffffff; /* Mask out top 6 bits */
}

static inline int flat_set_persistent(unsigned long relval,
				      unsigned long *persistent)
{
	int type = (relval >> 26) & 7;
	if (type == 3) {
		*persistent = relval << 16;
		return 1;
	}
	return 0;
}

static inline int flat_addr_absolute(unsigned long relval)
{
	return (relval & (1 << 29)) != 0;
}

#endif				/* __BLACKFIN_FLAT_H__ */
