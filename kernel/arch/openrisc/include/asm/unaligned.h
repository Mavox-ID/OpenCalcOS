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
#ifndef __ASM_OPENRISC_UNALIGNED_H
#define __ASM_OPENRISC_UNALIGNED_H

/*
 * This is copied from the generic implementation and the C-struct
 * variant replaced with the memmove variant.  The GCC compiler
 * for the OR32 arch optimizes too aggressively for the C-struct
 * variant to work, so use the memmove variant instead.
 *
 * It may be worth considering implementing the unaligned access
 * exception handler and allowing unaligned accesses (access_ok.h)...
 * not sure if it would be much of a performance win without further
 * investigation.
 */
#include <asm/byteorder.h>

#if defined(__LITTLE_ENDIAN)
# include <beep/unaligned/le_memmove.h>
# include <beep/unaligned/be_byteshift.h>
# include <beep/unaligned/generic.h>
# define get_unaligned	__get_unaligned_le
# define put_unaligned	__put_unaligned_le
#elif defined(__BIG_ENDIAN)
# include <beep/unaligned/be_memmove.h>
# include <beep/unaligned/le_byteshift.h>
# include <beep/unaligned/generic.h>
# define get_unaligned	__get_unaligned_be
# define put_unaligned	__put_unaligned_be
#else
# error need to define endianess
#endif

#endif /* __ASM_OPENRISC_UNALIGNED_H */
