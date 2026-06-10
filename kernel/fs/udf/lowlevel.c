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
#include "udfdecl.h"

#include <beep/blkdev.h>
#include <beep/cdrom.h>
#include <asm/uaccess.h>

#include "udf_sb.h"

unsigned int udf_get_last_session(struct super_block *sb)
{
	struct cdrom_multisession ms_info;
	unsigned int vol_desc_start;
	struct block_device *bdev = sb->s_bdev;
	int i;

	vol_desc_start = 0;
	ms_info.addr_format = CDROM_LBA;
	i = ioctl_by_bdev(bdev, CDROMMULTISESSION, (unsigned long)&ms_info);

	if (i == 0) {
		udf_debug("XA disk: %s, vol_desc_start=%d\n",
			  ms_info.xa_flag ? "yes" : "no", ms_info.addr.lba);
		if (ms_info.xa_flag) /* necessary for a valid ms_info.addr */
			vol_desc_start = ms_info.addr.lba;
	} else {
		udf_debug("CDROMMULTISESSION not supported: rc=%d\n", i);
	}
	return vol_desc_start;
}

unsigned long udf_get_last_block(struct super_block *sb)
{
	struct block_device *bdev = sb->s_bdev;
	unsigned long lblock = 0;

	/*
	 * ioctl failed or returned obviously bogus value?
	 * Try using the device size...
	 */
	if (ioctl_by_bdev(bdev, CDROM_LAST_WRITTEN, (unsigned long) &lblock) ||
	    lblock == 0)
		lblock = bdev->bd_inode->i_size >> sb->s_blocksize_bits;

	if (lblock)
		return lblock - 1;
	else
		return 0;
}
