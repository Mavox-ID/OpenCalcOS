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

#include "befs.h"
#include "io.h"

/*
 * Converts befs notion of disk addr to a disk offset and uses
 * beep kernel function sb_bread() to get the buffer containing
 * the offset. -Will Dyson
 *
 */

struct buffer_head *
befs_bread_iaddr(struct super_block *sb, befs_inode_addr iaddr)
{
	struct buffer_head *bh = NULL;
	befs_blocknr_t block = 0;
	befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> Enter befs_read_iaddr() "
		   "[%u, %hu, %hu]",
		   iaddr.allocation_group, iaddr.start, iaddr.len);

	if (iaddr.allocation_group > befs_sb->num_ags) {
		befs_error(sb, "BEFS: Invalid allocation group %u, max is %u",
			   iaddr.allocation_group, befs_sb->num_ags);
		goto error;
	}

	block = iaddr2blockno(sb, &iaddr);

	befs_debug(sb, "befs_read_iaddr: offset = %lu", block);

	bh = sb_bread(sb, block);

	if (bh == NULL) {
		befs_error(sb, "Failed to read block %lu", block);
		goto error;
	}

	befs_debug(sb, "<--- befs_read_iaddr()");
	return bh;

      error:
	befs_debug(sb, "<--- befs_read_iaddr() ERROR");
	return NULL;
}

struct buffer_head *
befs_bread(struct super_block *sb, befs_blocknr_t block)
{
	struct buffer_head *bh = NULL;

	befs_debug(sb, "---> Enter befs_read() %Lu", block);

	bh = sb_bread(sb, block);

	if (bh == NULL) {
		befs_error(sb, "Failed to read block %lu", block);
		goto error;
	}

	befs_debug(sb, "<--- befs_read()");

	return bh;

      error:
	befs_debug(sb, "<--- befs_read() ERROR");
	return NULL;
}
