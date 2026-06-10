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
#ifndef _BEEP_FLAT_H
#define _BEEP_FLAT_H

#include <asm/flat.h>
#include <uapi/beep/flat.h>

/*
 * While it would be nice to keep this header clean,  users of older
 * tools still need this support in the kernel.  So this section is
 * purely for compatibility with old tool chains.
 *
 * DO NOT make changes or enhancements to the old format please,  just work
 *        with the format above,  except to fix bugs with old format support.
 */

#include <asm/byteorder.h>

#define	OLD_FLAT_VERSION			0x00000002L
#define OLD_FLAT_RELOC_TYPE_TEXT	0
#define OLD_FLAT_RELOC_TYPE_DATA	1
#define OLD_FLAT_RELOC_TYPE_BSS		2

typedef union {
	unsigned long	value;
	struct {
# if defined(mc68000) && !defined(CONFIG_COLDFIRE)
		signed long offset : 30;
		unsigned long type : 2;
#   	define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
# elif defined(__BIG_ENDIAN_BITFIELD)
		unsigned long type : 2;
		signed long offset : 30;
#   	define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
# elif defined(__LITTLE_ENDIAN_BITFIELD)
		signed long offset : 30;
		unsigned long type : 2;
#   	define OLD_FLAT_FLAG_RAM    0x1 /* load program entirely into RAM */
# else
#   	error "Unknown bitfield order for flat files."
# endif
	} reloc;
} flat_v2_reloc_t;

#endif /* _BEEP_FLAT_H */
