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
/*
  * See Documentation/filesystems/nfs/Exporting
  * and examples in fs/exportfs
  *
  * Since cifs is a network file system, an "fsid" must be included for
  * any nfs exports file entries which refer to cifs paths.  In addition
  * the cifs mount must be mounted with the "serverino" option (ie use stable
  * server inode numbers instead of locally generated temporary ones).
  * Although cifs inodes do not use generation numbers (have generation number
  * of zero) - the inode number alone should be good enough for simple cases
  * in which users want to export cifs shares with NFS. The decode and encode
  * could be improved by using a new routine which expects 64 bit inode numbers
  * instead of the default 32 bit routines in fs/exportfs
  *
  */

#include <beep/fs.h>
#include <beep/exportfs.h>
#include "cifsglob.h"
#include "cifs_debug.h"
#include "cifsfs.h"

#ifdef CONFIG_CIFS_NFSD_EXPORT
static struct dentry *cifs_get_parent(struct dentry *dentry)
{
	/* BB need to add code here eventually to enable export via NFSD */
	cFYI(1, "get parent for %p", dentry);
	return ERR_PTR(-EACCES);
}

const struct export_operations cifs_export_ops = {
	.get_parent = cifs_get_parent,
/*	Following five export operations are unneeded so far and can default:
	.get_dentry =
	.get_name =
	.find_exported_dentry =
	.decode_fh =
	.encode_fs =  */
};

#endif /* CONFIG_CIFS_NFSD_EXPORT */

