/*
 * Symlink inode operations for Coda filesystem
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten for Beep 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
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
