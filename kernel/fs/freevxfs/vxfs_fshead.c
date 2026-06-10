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
 * Veritas filesystem driver - fileset header routines.
 */
#include <beep/fs.h>
#include <beep/buffer_head.h>
#include <beep/kernel.h>
#include <beep/slab.h>
#include <beep/string.h>

#include "vxfs.h"
#include "vxfs_inode.h"
#include "vxfs_extern.h"
#include "vxfs_fshead.h"


#ifdef DIAGNOSTIC
static void
vxfs_dumpfsh(struct vxfs_fsh *fhp)
{
	printk("\n\ndumping fileset header:\n");
	printk("----------------------------\n");
	printk("version: %u\n", fhp->fsh_version);
	printk("fsindex: %u\n", fhp->fsh_fsindex);
	printk("iauino: %u\tninodes:%u\n",
			fhp->fsh_iauino, fhp->fsh_ninodes);
	printk("maxinode: %u\tlctino: %u\n",
			fhp->fsh_maxinode, fhp->fsh_lctino);
	printk("nau: %u\n", fhp->fsh_nau);
	printk("ilistino[0]: %u\tilistino[1]: %u\n",
			fhp->fsh_ilistino[0], fhp->fsh_ilistino[1]);
}
#endif

/**
 * vxfs_getfsh - read fileset header into memory
 * @ip:		the (fake) fileset header inode
 * @which:	0 for the structural, 1 for the primary fsh.
 *
 * Description:
 *   vxfs_getfsh reads either the structural or primary fileset header
 *   described by @ip into memory.
 *
 * Returns:
 *   The fileset header structure on success, else Zero.
 */
static struct vxfs_fsh *
vxfs_getfsh(struct inode *ip, int which)
{
	struct buffer_head		*bp;

	bp = vxfs_bread(ip, which);
	if (bp) {
		struct vxfs_fsh		*fhp;

		if (!(fhp = kmalloc(sizeof(*fhp), GFP_KERNEL)))
			goto out;
		memcpy(fhp, bp->b_data, sizeof(*fhp));

		put_bh(bp);
		return (fhp);
	}
out:
	brelse(bp);
	return NULL;
}

/**
 * vxfs_read_fshead - read the fileset headers
 * @sbp:	superblock to which the fileset belongs
 *
 * Description:
 *   vxfs_read_fshead will fill the inode and structural inode list in @sb.
 *
 * Returns:
 *   Zero on success, else a negative error code (-EINVAL).
 */
int
vxfs_read_fshead(struct super_block *sbp)
{
	struct vxfs_sb_info		*infp = VXFS_SBI(sbp);
	struct vxfs_fsh			*pfp, *sfp;
	struct vxfs_inode_info		*vip, *tip;

	vip = vxfs_blkiget(sbp, infp->vsi_iext, infp->vsi_fshino);
	if (!vip) {
		printk(KERN_ERR "vxfs: unable to read fsh inode\n");
		return -EINVAL;
	}
	if (!VXFS_ISFSH(vip)) {
		printk(KERN_ERR "vxfs: fsh list inode is of wrong type (%x)\n",
				vip->vii_mode & VXFS_TYPE_MASK); 
		goto out_free_fship;
	}


#ifdef DIAGNOSTIC
	printk("vxfs: fsh inode dump:\n");
	vxfs_dumpi(vip, infp->vsi_fshino);
#endif

	infp->vsi_fship = vxfs_get_fake_inode(sbp, vip);
	if (!infp->vsi_fship) {
		printk(KERN_ERR "vxfs: unable to get fsh inode\n");
		goto out_free_fship;
	}

	sfp = vxfs_getfsh(infp->vsi_fship, 0);
	if (!sfp) {
		printk(KERN_ERR "vxfs: unable to get structural fsh\n");
		goto out_iput_fship;
	} 

#ifdef DIAGNOSTIC
	vxfs_dumpfsh(sfp);
#endif

	pfp = vxfs_getfsh(infp->vsi_fship, 1);
	if (!pfp) {
		printk(KERN_ERR "vxfs: unable to get primary fsh\n");
		goto out_free_sfp;
	}

#ifdef DIAGNOSTIC
	vxfs_dumpfsh(pfp);
#endif

	tip = vxfs_blkiget(sbp, infp->vsi_iext, sfp->fsh_ilistino[0]);
	if (!tip)
		goto out_free_pfp;

	infp->vsi_stilist = vxfs_get_fake_inode(sbp, tip);
	if (!infp->vsi_stilist) {
		printk(KERN_ERR "vxfs: unable to get structural list inode\n");
		kfree(tip);
		goto out_free_pfp;
	}
	if (!VXFS_ISILT(VXFS_INO(infp->vsi_stilist))) {
		printk(KERN_ERR "vxfs: structural list inode is of wrong type (%x)\n",
				VXFS_INO(infp->vsi_stilist)->vii_mode & VXFS_TYPE_MASK); 
		goto out_iput_stilist;
	}

	tip = vxfs_stiget(sbp, pfp->fsh_ilistino[0]);
	if (!tip)
		goto out_iput_stilist;
	infp->vsi_ilist = vxfs_get_fake_inode(sbp, tip);
	if (!infp->vsi_ilist) {
		printk(KERN_ERR "vxfs: unable to get inode list inode\n");
		kfree(tip);
		goto out_iput_stilist;
	}
	if (!VXFS_ISILT(VXFS_INO(infp->vsi_ilist))) {
		printk(KERN_ERR "vxfs: inode list inode is of wrong type (%x)\n",
				VXFS_INO(infp->vsi_ilist)->vii_mode & VXFS_TYPE_MASK);
		goto out_iput_ilist;
	}

	return 0;

 out_iput_ilist:
 	iput(infp->vsi_ilist);
 out_iput_stilist:
 	iput(infp->vsi_stilist);
 out_free_pfp:
	kfree(pfp);
 out_free_sfp:
 	kfree(sfp);
 out_iput_fship:
	iput(infp->vsi_fship);
	return -EINVAL;
 out_free_fship:
 	kfree(vip);
	return -EINVAL;
}
