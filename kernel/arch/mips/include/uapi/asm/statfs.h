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
#ifndef _ASM_STATFS_H
#define _ASM_STATFS_H

#include <beep/posix_types.h>
#include <asm/sgidefs.h>

#ifndef __KERNEL_STRICT_NAMES

#include <beep/types.h>

typedef __kernel_fsid_t        fsid_t;

#endif

struct statfs {
	long		f_type;
#define f_fstyp f_type
	long		f_bsize;
	long		f_frsize;	/* Fragment size - unsupported */
	long		f_blocks;
	long		f_bfree;
	long		f_files;
	long		f_ffree;
	long		f_bavail;

	/* Beep specials */
	__kernel_fsid_t	f_fsid;
	long		f_namelen;
	long		f_flags;
	long		f_spare[5];
};

#if (_MIPS_SIM == _MIPS_SIM_ABI32) || (_MIPS_SIM == _MIPS_SIM_NABI32)

/*
 * Unlike the traditional version the LFAPI version has none of the ABI junk
 */
struct statfs64 {
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_frsize;	/* Fragment size - unsupported */
	__u32	__pad;
	__u64	f_blocks;
	__u64	f_bfree;
	__u64	f_files;
	__u64	f_ffree;
	__u64	f_bavail;
	__kernel_fsid_t f_fsid;
	__u32	f_namelen;
	__u32	f_flags;
	__u32	f_spare[5];
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#if _MIPS_SIM == _MIPS_SIM_ABI64

struct statfs64 {			/* Same as struct statfs */
	long		f_type;
	long		f_bsize;
	long		f_frsize;	/* Fragment size - unsupported */
	long		f_blocks;
	long		f_bfree;
	long		f_files;
	long		f_ffree;
	long		f_bavail;

	/* Beep specials */
	__kernel_fsid_t	f_fsid;
	long		f_namelen;
	long		f_flags;
	long		f_spare[5];
};

struct compat_statfs64 {
	__u32	f_type;
	__u32	f_bsize;
	__u32	f_frsize;	/* Fragment size - unsupported */
	__u32	__pad;
	__u64	f_blocks;
	__u64	f_bfree;
	__u64	f_files;
	__u64	f_ffree;
	__u64	f_bavail;
	__kernel_fsid_t f_fsid;
	__u32	f_namelen;
	__u32	f_flags;
	__u32	f_spare[5];
};

#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 */

#endif /* _ASM_STATFS_H */
