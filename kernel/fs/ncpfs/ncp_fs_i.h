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
#ifndef _BEEP_NCP_FS_I
#define _BEEP_NCP_FS_I

/*
 * This is the ncpfs part of the inode structure. This must contain
 * all the information we need to work with an inode after creation.
 */
struct ncp_inode_info {
	__le32	dirEntNum;
	__le32	DosDirNum;
	__u8	volNumber;
	__le32	nwattr;
	struct mutex open_mutex;
	atomic_t	opened;
	int	access;
	int	flags;
#define NCPI_KLUDGE_SYMLINK	0x0001
	__u8	file_handle[6];
	struct inode vfs_inode;
};

#endif	/* _BEEP_NCP_FS_I */
