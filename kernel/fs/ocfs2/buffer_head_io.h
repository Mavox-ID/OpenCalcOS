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
#ifndef OCFS2_BUFFER_HEAD_IO_H
#define OCFS2_BUFFER_HEAD_IO_H

#include <beep/buffer_head.h>

void ocfs2_end_buffer_io_sync(struct buffer_head *bh,
			     int uptodate);

int ocfs2_write_block(struct ocfs2_super          *osb,
		      struct buffer_head  *bh,
		      struct ocfs2_caching_info   *ci);
int ocfs2_read_blocks_sync(struct ocfs2_super *osb, u64 block,
			   unsigned int nr, struct buffer_head *bhs[]);

/*
 * If not NULL, validate() will be called on a buffer that is freshly
 * read from disk.  It will not be called if the buffer was in cache.
 * Note that if validate() is being used for this buffer, it needs to
 * be set even for a READAHEAD call, as it marks the buffer for later
 * validation.
 */
int ocfs2_read_blocks(struct ocfs2_caching_info *ci, u64 block, int nr,
		      struct buffer_head *bhs[], int flags,
		      int (*validate)(struct super_block *sb,
				      struct buffer_head *bh));

int ocfs2_write_super_or_backup(struct ocfs2_super *osb,
				struct buffer_head *bh);

#define OCFS2_BH_IGNORE_CACHE      1
#define OCFS2_BH_READAHEAD         8

static inline int ocfs2_read_block(struct ocfs2_caching_info *ci, u64 off,
				   struct buffer_head **bh,
				   int (*validate)(struct super_block *sb,
						   struct buffer_head *bh))
{
	int status = 0;

	if (bh == NULL) {
		printk("ocfs2: bh == NULL\n");
		status = -EINVAL;
		goto bail;
	}

	status = ocfs2_read_blocks(ci, off, 1, bh, 0, validate);

bail:
	return status;
}

#endif /* OCFS2_BUFFER_HEAD_IO_H */
