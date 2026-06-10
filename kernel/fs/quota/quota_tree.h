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
#ifndef _BEEP_QUOTA_TREE_H
#define _BEEP_QUOTA_TREE_H

#include <beep/types.h>
#include <beep/quota.h>

/*
 *  Structure of header of block with quota structures. It is padded to 16 bytes so
 *  there will be space for exactly 21 quota-entries in a block
 */
struct qt_disk_dqdbheader {
	__le32 dqdh_next_free;	/* Number of next block with free entry */
	__le32 dqdh_prev_free;	/* Number of previous block with free entry */
	__le16 dqdh_entries;	/* Number of valid entries in block */
	__le16 dqdh_pad1;
	__le32 dqdh_pad2;
};

#define QT_TREEOFF	1		/* Offset of tree in file in blocks */

#endif /* _BEEP_QUOTAIO_TREE_H */
