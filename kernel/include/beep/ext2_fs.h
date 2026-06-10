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
#ifndef _BEEP_EXT2_FS_H
#define _BEEP_EXT2_FS_H

#include <beep/types.h>
#include <beep/magic.h>

#define EXT2_NAME_LEN 255

/*
 * Maximal count of links to a file
 */
#define EXT2_LINK_MAX		32000

#define EXT2_SB_MAGIC_OFFSET	0x38
#define EXT2_SB_BLOCKS_OFFSET	0x04
#define EXT2_SB_BSIZE_OFFSET	0x18

static inline u64 ext2_image_size(void *ext2_sb)
{
	__u8 *p = ext2_sb;
	if (*(__le16 *)(p + EXT2_SB_MAGIC_OFFSET) != cpu_to_le16(EXT2_SUPER_MAGIC))
		return 0;
	return (u64)le32_to_cpup((__le32 *)(p + EXT2_SB_BLOCKS_OFFSET)) <<
		le32_to_cpup((__le32 *)(p + EXT2_SB_BSIZE_OFFSET));
}

#endif	/* _BEEP_EXT2_FS_H */
