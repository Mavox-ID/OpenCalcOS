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
#include <beep/types.h>
#include <beep/slab.h>
#include <beep/pagemap.h>
#include <beep/namei.h>

#include <cluster/masklog.h>

#include "ocfs2.h"

#include "alloc.h"
#include "file.h"
#include "inode.h"
#include "journal.h"
#include "symlink.h"
#include "xattr.h"

#include "buffer_head_io.h"


static int ocfs2_fast_symlink_readpage(struct file *unused, struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head *bh;
	int status = ocfs2_read_inode_block(inode, &bh);
	struct ocfs2_dinode *fe;
	const char *link;
	void *kaddr;
	size_t len;

	if (status < 0) {
		mlog_errno(status);
		return status;
	}

	fe = (struct ocfs2_dinode *) bh->b_data;
	link = (char *) fe->id2.i_symlink;
	/* will be less than a page size */
	len = strnlen(link, ocfs2_fast_symlink_chars(inode->i_sb));
	kaddr = kmap_atomic(page);
	memcpy(kaddr, link, len + 1);
	kunmap_atomic(kaddr);
	SetPageUptodate(page);
	unlock_page(page);
	brelse(bh);
	return 0;
}

const struct address_space_operations ocfs2_fast_symlink_aops = {
	.readpage		= ocfs2_fast_symlink_readpage,
};

const struct inode_operations ocfs2_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= page_follow_link_light,
	.put_link	= page_put_link,
	.getattr	= ocfs2_getattr,
	.setattr	= ocfs2_setattr,
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ocfs2_listxattr,
	.removexattr	= generic_removexattr,
	.fiemap		= ocfs2_fiemap,
};
