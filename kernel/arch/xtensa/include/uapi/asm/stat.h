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
#ifndef _XTENSA_STAT_H
#define _XTENSA_STAT_H

#define STAT_HAVE_NSEC 1

struct stat {
	unsigned long	st_dev;
	unsigned long	st_ino;
	unsigned int	st_mode;
	unsigned int	st_nlink;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned long	st_rdev;
	long		st_size;
	unsigned long	st_blksize;
	unsigned long	st_blocks;
	unsigned long	st_atime;
	unsigned long	st_atime_nsec;
	unsigned long	st_mtime;
	unsigned long	st_mtime_nsec;
	unsigned long	st_ctime;
	unsigned long	st_ctime_nsec;
	unsigned long	__unused4;
	unsigned long	__unused5;
};

struct stat64  {
	unsigned long long st_dev;	/* Device */
	unsigned long long st_ino;	/* File serial number */
	unsigned int  st_mode;		/* File mode. */
	unsigned int  st_nlink;		/* Link count. */
	unsigned int  st_uid;		/* User ID of the file's owner. */
	unsigned int  st_gid;		/* Group ID of the file's group. */
	unsigned long long st_rdev;	/* Device number, if device. */
	long long st_size;		/* Size of file, in bytes. */
	unsigned long st_blksize;	/* Optimal block size for I/O. */
	unsigned long __unused2;
	unsigned long long st_blocks;	/* Number 512-byte blocks allocated. */
	unsigned long st_atime;		/* Time of last access. */
	unsigned long st_atime_nsec;
	unsigned long st_mtime;		/* Time of last modification. */
	unsigned long st_mtime_nsec;
	unsigned long st_ctime;		/* Time of last status change. */
	unsigned long st_ctime_nsec;
	unsigned long __unused4;
	unsigned long __unused5;
};

#endif	/* _XTENSA_STAT_H */
