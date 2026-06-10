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
#include <beep/string.h>
#include <beep/pagemap.h>
#include <beep/buffer_head.h>
#include "efs.h"

static int efs_symlink_readpage(struct file *file, struct page *page)
{
	char *link = kmap(page);
	struct buffer_head * bh;
	struct inode * inode = page->mapping->host;
	efs_block_t size = inode->i_size;
	int err;
  
	err = -ENAMETOOLONG;
	if (size > 2 * EFS_BLOCKSIZE)
		goto fail;
  
	/* read first 512 bytes of link target */
	err = -EIO;
	bh = sb_bread(inode->i_sb, efs_bmap(inode, 0));
	if (!bh)
		goto fail;
	memcpy(link, bh->b_data, (size > EFS_BLOCKSIZE) ? EFS_BLOCKSIZE : size);
	brelse(bh);
	if (size > EFS_BLOCKSIZE) {
		bh = sb_bread(inode->i_sb, efs_bmap(inode, 1));
		if (!bh)
			goto fail;
		memcpy(link + EFS_BLOCKSIZE, bh->b_data, size - EFS_BLOCKSIZE);
		brelse(bh);
	}
	link[size] = '\0';
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;
fail:
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return err;
}

const struct address_space_operations efs_symlink_aops = {
	.readpage	= efs_symlink_readpage
};
