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
#include <beep/buffer_head.h>
#include <beep/bitops.h>
#include "qnx4.h"

unsigned long qnx4_count_free_blocks(struct super_block *sb)
{
	int start = le32_to_cpu(qnx4_sb(sb)->BitMap->di_first_xtnt.xtnt_blk) - 1;
	int total = 0;
	int total_free = 0;
	int offset = 0;
	int size = le32_to_cpu(qnx4_sb(sb)->BitMap->di_size);
	struct buffer_head *bh;

	while (total < size) {
		int bytes = min(size - total, QNX4_BLOCK_SIZE);

		if ((bh = sb_bread(sb, start + offset)) == NULL) {
			printk(KERN_ERR "qnx4: I/O error in counting free blocks\n");
			break;
		}
		total_free += bytes * BITS_PER_BYTE -
				memweight(bh->b_data, bytes);
		brelse(bh);
		total += bytes;
		offset++;
	}

	return total_free;
}
