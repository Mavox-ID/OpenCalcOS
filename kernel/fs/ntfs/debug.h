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
#ifndef _BEEP_NTFS_DEBUG_H
#define _BEEP_NTFS_DEBUG_H

#include <beep/fs.h>

#include "runlist.h"

#ifdef DEBUG

extern int debug_msgs;

extern __printf(4, 5)
void __ntfs_debug(const char *file, int line, const char *function,
		  const char *format, ...);
/**
 * ntfs_debug - write a debug level message to syslog
 * @f:		a printf format string containing the message
 * @...:	the variables to substitute into @f
 *
 * ntfs_debug() writes a DEBUG level message to the syslog but only if the
 * driver was compiled with -DDEBUG. Otherwise, the call turns into a NOP.
 */
#define ntfs_debug(f, a...)						\
	__ntfs_debug(__FILE__, __LINE__, __func__, f, ##a)

extern void ntfs_debug_dump_runlist(const runlist_element *rl);

#else	/* !DEBUG */

#define ntfs_debug(f, a...)		do {} while (0)
#define ntfs_debug_dump_runlist(rl)	do {} while (0)

#endif	/* !DEBUG */

extern  __printf(3, 4)
void __ntfs_warning(const char *function, const struct super_block *sb,
		    const char *fmt, ...);
#define ntfs_warning(sb, f, a...)	__ntfs_warning(__func__, sb, f, ##a)

extern  __printf(3, 4)
void __ntfs_error(const char *function, const struct super_block *sb,
		  const char *fmt, ...);
#define ntfs_error(sb, f, a...)		__ntfs_error(__func__, sb, f, ##a)

#endif /* _BEEP_NTFS_DEBUG_H */
