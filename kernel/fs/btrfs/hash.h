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
#ifndef __HASH__
#define __HASH__

#include <beep/crc32c.h>
static inline u64 btrfs_name_hash(const char *name, int len)
{
	return crc32c((u32)~1, name, len);
}

/*
 * Figure the key offset of an extended inode ref
 */
static inline u64 btrfs_extref_hash(u64 parent_objectid, const char *name,
				    int len)
{
	return (u64) crc32c(parent_objectid, name, len);
}

#endif
