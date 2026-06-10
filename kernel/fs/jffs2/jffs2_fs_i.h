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
#ifndef _JFFS2_FS_I
#define _JFFS2_FS_I

#include <beep/rbtree.h>
#include <beep/posix_acl.h>
#include <beep/mutex.h>

struct jffs2_inode_info {
	/* We need an internal mutex similar to inode->i_mutex.
	   Unfortunately, we can't used the existing one, because
	   either the GC would deadlock, or we'd have to release it
	   before letting GC proceed. Or we'd have to put ugliness
	   into the GC code so it didn't attempt to obtain the i_mutex
	   for the inode(s) which are already locked */
	struct mutex sem;

	/* The highest (datanode) version number used for this ino */
	uint32_t highest_version;

	/* List of data fragments which make up the file */
	struct rb_root fragtree;

	/* There may be one datanode which isn't referenced by any of the
	   above fragments, if it contains a metadata update but no actual
	   data - or if this is a directory inode */
	/* This also holds the _only_ dnode for symlinks/device nodes,
	   etc. */
	struct jffs2_full_dnode *metadata;

	/* Directory entries */
	struct jffs2_full_dirent *dents;

	/* The target path if this is the inode of a symlink */
	unsigned char *target;

	/* Some stuff we just have to keep in-core at all times, for each inode. */
	struct jffs2_inode_cache *inocache;

	uint16_t flags;
	uint8_t usercompr;
	struct inode vfs_inode;
};

#endif /* _JFFS2_FS_I */
