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
#include <beep/slab.h>
#include "hfsplus_fs.h"

/* offsets to various blocks */
#define HFS_DD_BLK		0 /* Driver Descriptor block */
#define HFS_PMAP_BLK		1 /* First block of partition map */
#define HFS_MDB_BLK		2 /* Block (w/i partition) of MDB */

/* magic numbers for various disk blocks */
#define HFS_DRVR_DESC_MAGIC	0x4552 /* "ER": driver descriptor map */
#define HFS_OLD_PMAP_MAGIC	0x5453 /* "TS": old-type partition map */
#define HFS_NEW_PMAP_MAGIC	0x504D /* "PM": new-type partition map */
#define HFS_SUPER_MAGIC		0x4244 /* "BD": HFS MDB (super block) */
#define HFS_MFS_SUPER_MAGIC	0xD2D7 /* MFS MDB (super block) */

/*
 * The new style Mac partition map
 *
 * For each partition on the media there is a physical block (512-byte
 * block) containing one of these structures.  These blocks are
 * contiguous starting at block 1.
 */
struct new_pmap {
	__be16	pmSig;		/* signature */
	__be16	reSigPad;	/* padding */
	__be32	pmMapBlkCnt;	/* partition blocks count */
	__be32	pmPyPartStart;	/* physical block start of partition */
	__be32	pmPartBlkCnt;	/* physical block count of partition */
	u8	pmPartName[32];	/* (null terminated?) string
				   giving the name of this
				   partition */
	u8	pmPartType[32];	/* (null terminated?) string
				   giving the type of this
				   partition */
	/* a bunch more stuff we don't need */
} __packed;

/*
 * The old style Mac partition map
 *
 * The partition map consists for a 2-byte signature followed by an
 * array of these structures.  The map is terminated with an all-zero
 * one of these.
 */
struct old_pmap {
	__be16		pdSig;	/* Signature bytes */
	struct old_pmap_entry {
		__be32	pdStart;
		__be32	pdSize;
		__be32	pdFSID;
	}	pdEntry[42];
} __packed;

static int hfs_parse_old_pmap(struct super_block *sb, struct old_pmap *pm,
		sector_t *part_start, sector_t *part_size)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	int i;

	for (i = 0; i < 42; i++) {
		struct old_pmap_entry *p = &pm->pdEntry[i];

		if (p->pdStart && p->pdSize &&
		    p->pdFSID == cpu_to_be32(0x54465331)/*"TFS1"*/ &&
		    (sbi->part < 0 || sbi->part == i)) {
			*part_start += be32_to_cpu(p->pdStart);
			*part_size = be32_to_cpu(p->pdSize);
			return 0;
		}
	}

	return -ENOENT;
}

static int hfs_parse_new_pmap(struct super_block *sb, void *buf,
		struct new_pmap *pm, sector_t *part_start, sector_t *part_size)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	int size = be32_to_cpu(pm->pmMapBlkCnt);
	int buf_size = hfsplus_min_io_size(sb);
	int res;
	int i = 0;

	do {
		if (!memcmp(pm->pmPartType, "Apple_HFS", 9) &&
		    (sbi->part < 0 || sbi->part == i)) {
			*part_start += be32_to_cpu(pm->pmPyPartStart);
			*part_size = be32_to_cpu(pm->pmPartBlkCnt);
			return 0;
		}

		if (++i >= size)
			return -ENOENT;

		pm = (struct new_pmap *)((u8 *)pm + HFSPLUS_SECTOR_SIZE);
		if ((u8 *)pm - (u8 *)buf >= buf_size) {
			res = hfsplus_submit_bio(sb,
						 *part_start + HFS_PMAP_BLK + i,
						 buf, (void **)&pm, READ);
			if (res)
				return res;
		}
	} while (pm->pmSig == cpu_to_be16(HFS_NEW_PMAP_MAGIC));

	return -ENOENT;
}

/*
 * Parse the partition map looking for the start and length of a
 * HFS/HFS+ partition.
 */
int hfs_part_find(struct super_block *sb,
		sector_t *part_start, sector_t *part_size)
{
	void *buf, *data;
	int res;

	buf = kmalloc(hfsplus_min_io_size(sb), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	res = hfsplus_submit_bio(sb, *part_start + HFS_PMAP_BLK,
				 buf, &data, READ);
	if (res)
		goto out;

	switch (be16_to_cpu(*((__be16 *)data))) {
	case HFS_OLD_PMAP_MAGIC:
		res = hfs_parse_old_pmap(sb, data, part_start, part_size);
		break;
	case HFS_NEW_PMAP_MAGIC:
		res = hfs_parse_new_pmap(sb, buf, data, part_start, part_size);
		break;
	default:
		res = -ENOENT;
		break;
	}
out:
	kfree(buf);
	return res;
}
