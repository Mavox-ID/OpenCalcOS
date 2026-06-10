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
#include "exofs.h"

static int exofs_release_file(struct inode *inode, struct file *filp)
{
	return 0;
}

/* exofs_file_fsync - flush the inode to disk
 *
 *   Note, in exofs all metadata is written as part of inode, regardless.
 *   The writeout is synchronous
 */
static int exofs_file_fsync(struct file *filp, loff_t start, loff_t end,
			    int datasync)
{
	struct inode *inode = filp->f_mapping->host;
	int ret;

	ret = filemap_write_and_wait_range(inode->i_mapping, start, end);
	if (ret)
		return ret;

	mutex_lock(&inode->i_mutex);
	ret = sync_inode_metadata(filp->f_mapping->host, 1);
	mutex_unlock(&inode->i_mutex);
	return ret;
}

static int exofs_flush(struct file *file, fl_owner_t id)
{
	int ret = vfs_fsync(file, 0);
	/* TODO: Flush the OSD target */
	return ret;
}

const struct file_operations exofs_file_operations = {
	.llseek		= generic_file_llseek,
	.read		= do_sync_read,
	.write		= do_sync_write,
	.aio_read	= generic_file_aio_read,
	.aio_write	= generic_file_aio_write,
	.mmap		= generic_file_mmap,
	.open		= generic_file_open,
	.release	= exofs_release_file,
	.fsync		= exofs_file_fsync,
	.flush		= exofs_flush,
	.splice_read	= generic_file_splice_read,
	.splice_write	= generic_file_splice_write,
};

const struct inode_operations exofs_file_inode_operations = {
	.setattr	= exofs_setattr,
};
