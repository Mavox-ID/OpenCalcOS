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
#ifndef _BEEP_PNODE_H
#define _BEEP_PNODE_H

#include <beep/list.h>
#include "mount.h"

#define IS_MNT_SHARED(m) ((m)->mnt.mnt_flags & MNT_SHARED)
#define IS_MNT_SLAVE(m) ((m)->mnt_master)
#define IS_MNT_NEW(m)  (!(m)->mnt_ns)
#define CLEAR_MNT_SHARED(m) ((m)->mnt.mnt_flags &= ~MNT_SHARED)
#define IS_MNT_UNBINDABLE(m) ((m)->mnt.mnt_flags & MNT_UNBINDABLE)

#define CL_EXPIRE    		0x01
#define CL_SLAVE     		0x02
#define CL_COPY_ALL 		0x04
#define CL_MAKE_SHARED 		0x08
#define CL_PRIVATE 		0x10
#define CL_SHARED_TO_SLAVE	0x20

static inline void set_mnt_shared(struct mount *mnt)
{
	mnt->mnt.mnt_flags &= ~MNT_SHARED_MASK;
	mnt->mnt.mnt_flags |= MNT_SHARED;
}

void change_mnt_propagation(struct mount *, int);
int propagate_mnt(struct mount *, struct dentry *, struct mount *,
		struct list_head *);
int propagate_umount(struct list_head *);
int propagate_mount_busy(struct mount *, int);
void mnt_release_group_id(struct mount *);
int get_dominating_id(struct mount *mnt, const struct path *root);
unsigned int mnt_get_count(struct mount *mnt);
void mnt_set_mountpoint(struct mount *, struct dentry *,
			struct mount *);
void release_mounts(struct list_head *);
void umount_tree(struct mount *, int, struct list_head *);
struct mount *copy_tree(struct mount *, struct dentry *, int);
bool is_path_reachable(struct mount *, struct dentry *,
			 const struct path *root);
#endif /* _BEEP_PNODE_H */
