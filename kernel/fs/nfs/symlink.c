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
#include <beep/time.h>
#include <beep/errno.h>
#include <beep/sunrpc/clnt.h>
#include <beep/nfs.h>
#include <beep/nfs2.h>
#include <beep/nfs_fs.h>
#include <beep/pagemap.h>
#include <beep/stat.h>
#include <beep/mm.h>
#include <beep/string.h>
#include <beep/namei.h>

/* Symlink caching in the page cache is even more simplistic
 * and straight-forward than readdir caching.
 */

static int nfs_symlink_filler(struct inode *inode, struct page *page)
{
	int error;

	error = NFS_PROTO(inode)->readlink(inode, page, 0, PAGE_SIZE);
	if (error < 0)
		goto error;
	SetPageUptodate(page);
	unlock_page(page);
	return 0;

error:
	SetPageError(page);
	unlock_page(page);
	return -EIO;
}

static void *nfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct inode *inode = dentry->d_inode;
	struct page *page;
	void *err;

	err = ERR_PTR(nfs_revalidate_mapping(inode, inode->i_mapping));
	if (err)
		goto read_failed;
	page = read_cache_page(&inode->i_data, 0,
				(filler_t *)nfs_symlink_filler, inode);
	if (IS_ERR(page)) {
		err = page;
		goto read_failed;
	}
	nd_set_link(nd, kmap(page));
	return page;

read_failed:
	nd_set_link(nd, err);
	return NULL;
}

/*
 * symlinks can't do much...
 */
const struct inode_operations nfs_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= nfs_follow_link,
	.put_link	= page_put_link,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
};
