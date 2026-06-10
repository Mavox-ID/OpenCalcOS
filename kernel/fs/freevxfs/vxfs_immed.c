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
 * Veritas filesystem driver - support for 'immed' inodes.
 */
#include <beep/fs.h>
#include <beep/pagemap.h>
#include <beep/namei.h>

#include "vxfs.h"
#include "vxfs_extern.h"
#include "vxfs_inode.h"


static void *	vxfs_immed_follow_link(struct dentry *, struct nameidata *);

static int	vxfs_immed_readpage(struct file *, struct page *);

/*
 * Inode operations for immed symlinks.
 *
 * Unliked all other operations we do not go through the pagecache,
 * but do all work directly on the inode.
 */
const struct inode_operations vxfs_immed_symlink_iops = {
	.readlink =		generic_readlink,
	.follow_link =		vxfs_immed_follow_link,
};

/*
 * Address space operations for immed files and directories.
 */
const struct address_space_operations vxfs_immed_aops = {
	.readpage =		vxfs_immed_readpage,
};

/**
 * vxfs_immed_follow_link - follow immed symlink
 * @dp:		dentry for the link
 * @np:		pathname lookup data for the current path walk
 *
 * Description:
 *   vxfs_immed_follow_link restarts the pathname lookup with
 *   the data obtained from @dp.
 *
 * Returns:
 *   Zero on success, else a negative error code.
 */
static void *
vxfs_immed_follow_link(struct dentry *dp, struct nameidata *np)
{
	struct vxfs_inode_info		*vip = VXFS_INO(dp->d_inode);
	nd_set_link(np, vip->vii_immed.vi_immed);
	return NULL;
}

/**
 * vxfs_immed_readpage - read part of an immed inode into pagecache
 * @file:	file context (unused)
 * @page:	page frame to fill in.
 *
 * Description:
 *   vxfs_immed_readpage reads a part of the immed area of the
 *   file that hosts @pp into the pagecache.
 *
 * Returns:
 *   Zero on success, else a negative error code.
 *
 * Locking status:
 *   @page is locked and will be unlocked.
 */
static int
vxfs_immed_readpage(struct file *fp, struct page *pp)
{
	struct vxfs_inode_info	*vip = VXFS_INO(pp->mapping->host);
	u_int64_t	offset = (u_int64_t)pp->index << PAGE_CACHE_SHIFT;
	caddr_t		kaddr;

	kaddr = kmap(pp);
	memcpy(kaddr, vip->vii_immed.vi_immed + offset, PAGE_CACHE_SIZE);
	kunmap(pp);
	
	flush_dcache_page(pp);
	SetPageUptodate(pp);
        unlock_page(pp);

	return 0;
}
