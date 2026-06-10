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
#ifndef _BEEP_NTFS_TYPES_H
#define _BEEP_NTFS_TYPES_H

#include <beep/types.h>

typedef __le16 le16;
typedef __le32 le32;
typedef __le64 le64;
typedef __u16 __bitwise sle16;
typedef __u32 __bitwise sle32;
typedef __u64 __bitwise sle64;

/* 2-byte Unicode character type. */
typedef le16 ntfschar;
#define UCHAR_T_SIZE_BITS 1

/*
 * Clusters are signed 64-bit values on NTFS volumes. We define two types, LCN
 * and VCN, to allow for type checking and better code readability.
 */
typedef s64 VCN;
typedef sle64 leVCN;
typedef s64 LCN;
typedef sle64 leLCN;

/*
 * The NTFS journal $LogFile uses log sequence numbers which are signed 64-bit
 * values.  We define our own type LSN, to allow for type checking and better
 * code readability.
 */
typedef s64 LSN;
typedef sle64 leLSN;

/*
 * The NTFS transaction log $UsnJrnl uses usn which are signed 64-bit values.
 * We define our own type USN, to allow for type checking and better code
 * readability.
 */
typedef s64 USN;
typedef sle64 leUSN;

typedef enum {
	CASE_SENSITIVE = 0,
	IGNORE_CASE = 1,
} IGNORE_CASE_BOOL;

#endif /* _BEEP_NTFS_TYPES_H */
