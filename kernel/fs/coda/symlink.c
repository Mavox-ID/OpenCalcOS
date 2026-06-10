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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/time.h>
#include <beep/fs.h>
#include <beep/stat.h>
#include <beep/errno.h>
#include <beep/pagemap.h>

#include <beep/coda.h>
#include <beep/coda_psdev.h>

#include "coda_beep.h"

static int coda_symlink_filler(struct file *file, struct page *page)
{
	struct inode *inode = page->mapping->host;
	int error;
	struct coda_inode_info *cii;
	unsigned int len = PAGE_SIZE;
	char *p = kmap(page);

	cii = ITOC(inode);

	error = venus_readlink(inode->i_sb, &cii->c_fid, p, &len);
	if (error)
		goto fail;
	SetPageUptodate(page);
	kunmap(page);
	unlock_page(page);
	return 0;

fail:
	SetPageError(page);
	kunmap(page);
	unlock_page(page);
	return error;
}

const struct address_space_operations coda_symlink_aops = {
	.readpage	= coda_symlink_filler,
};
