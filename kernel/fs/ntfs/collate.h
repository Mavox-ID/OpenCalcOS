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
#ifndef _BEEP_NTFS_COLLATE_H
#define _BEEP_NTFS_COLLATE_H

#include "types.h"
#include "volume.h"

static inline bool ntfs_is_collation_rule_supported(COLLATION_RULE cr) {
	int i;

	/*
	 * FIXME:  At the moment we only support COLLATION_BINARY and
	 * COLLATION_NTOFS_ULONG, so we return false for everything else for
	 * now.
	 */
	if (unlikely(cr != COLLATION_BINARY && cr != COLLATION_NTOFS_ULONG))
		return false;
	i = le32_to_cpu(cr);
	if (likely(((i >= 0) && (i <= 0x02)) ||
			((i >= 0x10) && (i <= 0x13))))
		return true;
	return false;
}

extern int ntfs_collate(ntfs_volume *vol, COLLATION_RULE cr,
		const void *data1, const int data1_len,
		const void *data2, const int data2_len);

#endif /* _BEEP_NTFS_COLLATE_H */
