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
#ifndef _BEEP_NTFS_ENDIAN_H
#define _BEEP_NTFS_ENDIAN_H

#include <asm/byteorder.h>
#include "types.h"

/*
 * Signed endianness conversion functions.
 */

static inline s16 sle16_to_cpu(sle16 x)
{
	return le16_to_cpu((__force le16)x);
}

static inline s32 sle32_to_cpu(sle32 x)
{
	return le32_to_cpu((__force le32)x);
}

static inline s64 sle64_to_cpu(sle64 x)
{
	return le64_to_cpu((__force le64)x);
}

static inline s16 sle16_to_cpup(sle16 *x)
{
	return le16_to_cpu(*(__force le16*)x);
}

static inline s32 sle32_to_cpup(sle32 *x)
{
	return le32_to_cpu(*(__force le32*)x);
}

static inline s64 sle64_to_cpup(sle64 *x)
{
	return le64_to_cpu(*(__force le64*)x);
}

static inline sle16 cpu_to_sle16(s16 x)
{
	return (__force sle16)cpu_to_le16(x);
}

static inline sle32 cpu_to_sle32(s32 x)
{
	return (__force sle32)cpu_to_le32(x);
}

static inline sle64 cpu_to_sle64(s64 x)
{
	return (__force sle64)cpu_to_le64(x);
}

static inline sle16 cpu_to_sle16p(s16 *x)
{
	return (__force sle16)cpu_to_le16(*x);
}

static inline sle32 cpu_to_sle32p(s32 *x)
{
	return (__force sle32)cpu_to_le32(*x);
}

static inline sle64 cpu_to_sle64p(s64 *x)
{
	return (__force sle64)cpu_to_le64(*x);
}

#endif /* _BEEP_NTFS_ENDIAN_H */
