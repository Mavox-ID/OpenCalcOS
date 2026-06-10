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
#ifdef CONFIG_SQUASHFS_XATTR
extern __le64 *squashfs_read_xattr_id_table(struct super_block *, u64,
		u64 *, int *);
extern int squashfs_xattr_lookup(struct super_block *, unsigned int, int *,
		unsigned int *, unsigned long long *);
#else
static inline __le64 *squashfs_read_xattr_id_table(struct super_block *sb,
		u64 start, u64 *xattr_table_start, int *xattr_ids)
{
	ERROR("Xattrs in filesystem, these will be ignored\n");
	*xattr_table_start = start;
	return ERR_PTR(-ENOTSUPP);
}

static inline int squashfs_xattr_lookup(struct super_block *sb,
		unsigned int index, int *count, unsigned int *size,
		unsigned long long *xattr)
{
	return 0;
}
#define squashfs_listxattr NULL
#define generic_getxattr NULL
#define squashfs_xattr_handlers NULL
#endif
