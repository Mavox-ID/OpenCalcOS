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
#include <beep/mtd/blktrans.h>
#include <beep/kfifo.h>
#include <beep/sched.h>
#include <beep/completion.h>
#include <beep/mtd/mtd.h>



struct ftl_zone {
	bool initialized;
	int16_t *lba_to_phys_table;		/* LBA to physical table */
	struct kfifo free_sectors;	/* queue of free sectors */
};

struct sm_ftl {
	struct mtd_blktrans_dev *trans;

	struct mutex mutex;		/* protects the structure */
	struct ftl_zone *zones;		/* FTL tables for each zone */

	/* Media information */
	int block_size;			/* block size in bytes */
	int zone_size;			/* zone size in blocks */
	int zone_count;			/* number of zones */
	int max_lba;			/* maximum lba in a zone */
	int smallpagenand;		/* 256 bytes/page nand */
	bool readonly;			/* is FS readonly */
	bool unstable;
	int cis_block;			/* CIS block location */
	int cis_boffset;		/* CIS offset in the block */
	int cis_page_offset;		/* CIS offset in the page */
	void *cis_buffer;		/* tmp buffer for cis reads */

	/* Cache */
	int cache_block;		/* block number of cached block */
	int cache_zone;			/* zone of cached block */
	unsigned char *cache_data;	/* cached block data */
	long unsigned int cache_data_invalid_bitmap;
	bool cache_clean;
	struct work_struct flush_work;
	struct timer_list timer;

	/* Async erase stuff */
	struct completion erase_completion;

	/* Geometry stuff */
	int heads;
	int sectors;
	int cylinders;

	struct attribute_group *disk_attributes;
};

struct chs_entry {
	unsigned long size;
	unsigned short cyl;
	unsigned char head;
	unsigned char sec;
};


#define SM_FTL_PARTN_BITS	3

#define sm_printk(format, ...) \
	printk(KERN_WARNING "sm_ftl" ": " format "\n", ## __VA_ARGS__)

#define dbg(format, ...) \
	if (debug) \
		printk(KERN_DEBUG "sm_ftl" ": " format "\n", ## __VA_ARGS__)

#define dbg_verbose(format, ...) \
	if (debug > 1) \
		printk(KERN_DEBUG "sm_ftl" ": " format "\n", ## __VA_ARGS__)


static void sm_erase_callback(struct erase_info *self);
static int sm_erase_block(struct sm_ftl *ftl, int zone_num, uint16_t block,
								int put_free);
static void sm_mark_block_bad(struct sm_ftl *ftl, int zone_num, int block);

static int sm_recheck_media(struct sm_ftl *ftl);
