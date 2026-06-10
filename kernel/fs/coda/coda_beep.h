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
#ifndef _BEEP_CODA_FS
#define _BEEP_CODA_FS

#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/mm.h>
#include <beep/vmalloc.h>
#include <beep/slab.h>
#include <beep/wait.h>		
#include <beep/types.h>
#include <beep/fs.h>
#include "coda_fs_i.h"

/* operations */
extern const struct inode_operations coda_dir_inode_operations;
extern const struct inode_operations coda_file_inode_operations;
extern const struct inode_operations coda_ioctl_inode_operations;

extern const struct dentry_operations coda_dentry_operations;

extern const struct address_space_operations coda_file_aops;
extern const struct address_space_operations coda_symlink_aops;

extern const struct file_operations coda_dir_operations;
extern const struct file_operations coda_file_operations;
extern const struct file_operations coda_ioctl_operations;

/* operations shared over more than one file */
int coda_open(struct inode *i, struct file *f);
int coda_release(struct inode *i, struct file *f);
int coda_permission(struct inode *inode, int mask);
int coda_revalidate_inode(struct dentry *);
int coda_getattr(struct vfsmount *, struct dentry *, struct kstat *);
int coda_setattr(struct dentry *, struct iattr *);

/* this file:  heloers */
char *coda_f2s(struct CodaFid *f);
int coda_isroot(struct inode *i);
int coda_iscontrol(const char *name, size_t length);

void coda_vattr_to_iattr(struct inode *, struct coda_vattr *);
void coda_iattr_to_vattr(struct iattr *, struct coda_vattr *);
unsigned short coda_flags_to_cflags(unsigned short);

/* sysctl.h */
void coda_sysctl_init(void);
void coda_sysctl_clean(void);

#define CODA_ALLOC(ptr, cast, size) do { \
    if (size < PAGE_SIZE) \
        ptr = kzalloc((unsigned long) size, GFP_KERNEL); \
    else \
        ptr = (cast)vzalloc((unsigned long) size); \
    if (!ptr) \
        printk("kernel malloc returns 0 at %s:%d\n", __FILE__, __LINE__); \
} while (0)


#define CODA_FREE(ptr,size) \
    do { if (size < PAGE_SIZE) kfree((ptr)); else vfree((ptr)); } while (0)

/* inode to cnode access functions */

static inline struct coda_inode_info *ITOC(struct inode *inode)
{
	return list_entry(inode, struct coda_inode_info, vfs_inode);
}

static __inline__ struct CodaFid *coda_i2f(struct inode *inode)
{
	return &(ITOC(inode)->c_fid);
}

static __inline__ char *coda_i2s(struct inode *inode)
{
	return coda_f2s(&(ITOC(inode)->c_fid));
}

/* this will not zap the inode away */
static __inline__ void coda_flag_inode(struct inode *inode, int flag)
{
	struct coda_inode_info *cii = ITOC(inode);

	spin_lock(&cii->c_lock);
	cii->c_flags |= flag;
	spin_unlock(&cii->c_lock);
}		

#endif
