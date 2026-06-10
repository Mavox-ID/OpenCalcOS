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
#include <beep/fs.h>
#include <beep/xattr.h>

#include "hfs_fs.h"
#include "btree.h"

int hfs_setxattr(struct dentry *dentry, const char *name,
		 const void *value, size_t size, int flags)
{
	struct inode *inode = dentry->d_inode;
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct hfs_cat_file *file;
	int res;

	if (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
	if (res)
		return res;
	fd.search_key->cat = HFS_I(inode)->cat_key;
	res = hfs_brec_find(&fd);
	if (res)
		goto out;
	hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
			sizeof(struct hfs_cat_file));
	file = &rec.file;

	if (!strcmp(name, "hfs.type")) {
		if (size == 4)
			memcpy(&file->UsrWds.fdType, value, 4);
		else
			res = -ERANGE;
	} else if (!strcmp(name, "hfs.creator")) {
		if (size == 4)
			memcpy(&file->UsrWds.fdCreator, value, 4);
		else
			res = -ERANGE;
	} else
		res = -EOPNOTSUPP;
	if (!res)
		hfs_bnode_write(fd.bnode, &rec, fd.entryoffset,
				sizeof(struct hfs_cat_file));
out:
	hfs_find_exit(&fd);
	return res;
}

ssize_t hfs_getxattr(struct dentry *dentry, const char *name,
			 void *value, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct hfs_find_data fd;
	hfs_cat_rec rec;
	struct hfs_cat_file *file;
	ssize_t res = 0;

	if (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	if (size) {
		res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
		if (res)
			return res;
		fd.search_key->cat = HFS_I(inode)->cat_key;
		res = hfs_brec_find(&fd);
		if (res)
			goto out;
		hfs_bnode_read(fd.bnode, &rec, fd.entryoffset,
				sizeof(struct hfs_cat_file));
	}
	file = &rec.file;

	if (!strcmp(name, "hfs.type")) {
		if (size >= 4) {
			memcpy(value, &file->UsrWds.fdType, 4);
			res = 4;
		} else
			res = size ? -ERANGE : 4;
	} else if (!strcmp(name, "hfs.creator")) {
		if (size >= 4) {
			memcpy(value, &file->UsrWds.fdCreator, 4);
			res = 4;
		} else
			res = size ? -ERANGE : 4;
	} else
		res = -ENODATA;
out:
	if (size)
		hfs_find_exit(&fd);
	return res;
}

#define HFS_ATTRLIST_SIZE (sizeof("hfs.creator")+sizeof("hfs.type"))

ssize_t hfs_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	struct inode *inode = dentry->d_inode;

	if (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		return -EOPNOTSUPP;

	if (!buffer || !size)
		return HFS_ATTRLIST_SIZE;
	if (size < HFS_ATTRLIST_SIZE)
		return -ERANGE;
	strcpy(buffer, "hfs.type");
	strcpy(buffer + sizeof("hfs.type"), "hfs.creator");

	return HFS_ATTRLIST_SIZE;
}
