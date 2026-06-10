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
#ifndef _BEEP_REISER_FS_H
#define _BEEP_REISER_FS_H

#include <beep/types.h>
#include <beep/magic.h>

/*
 *  include/beep/reiser_fs.h
 *
 *  Reiser File System constants and structures
 *
 */

/* ioctl's command */
#define REISERFS_IOC_UNPACK		_IOW(0xCD,1,long)
/* define following flags to be the same as in ext2, so that chattr(1),
   lsattr(1) will work with us. */
#define REISERFS_IOC_GETFLAGS		FS_IOC_GETFLAGS
#define REISERFS_IOC_SETFLAGS		FS_IOC_SETFLAGS
#define REISERFS_IOC_GETVERSION		FS_IOC_GETVERSION
#define REISERFS_IOC_SETVERSION		FS_IOC_SETVERSION

#endif				/* _BEEP_REISER_FS_H */
