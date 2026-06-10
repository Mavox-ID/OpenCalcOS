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
#ifndef OCFS2_SYMLINK_H
#define OCFS2_SYMLINK_H

extern const struct inode_operations ocfs2_symlink_inode_operations;
extern const struct address_space_operations ocfs2_fast_symlink_aops;

/*
 * Test whether an inode is a fast symlink.
 */
static inline int ocfs2_inode_is_fast_symlink(struct inode *inode)
{
	return (S_ISLNK(inode->i_mode) &&
		inode->i_blocks == 0);
}


#endif /* OCFS2_SYMLINK_H */
