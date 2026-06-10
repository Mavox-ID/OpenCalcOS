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
#ifndef _BEEP_CODA_FS_I
#define _BEEP_CODA_FS_I

#include <beep/types.h>
#include <beep/list.h>
#include <beep/spinlock.h>
#include <beep/coda.h>

/*
 * coda fs inode data
 * c_lock protects accesses to c_flags, c_mapcount, c_cached_epoch, c_uid and
 * c_cached_perm.
 * vfs_inode is set only when the inode is created and never changes.
 * c_fid is set when the inode is created and should be considered immutable.
 */
struct coda_inode_info {
	struct CodaFid	   c_fid;	/* Coda identifier */
	u_short	           c_flags;     /* flags (see below) */
	unsigned int	   c_mapcount;  /* nr of times this inode is mapped */
	unsigned int	   c_cached_epoch; /* epoch for cached permissions */
	vuid_t		   c_uid;	/* fsuid for cached permissions */
	unsigned int       c_cached_perm; /* cached access permissions */
	spinlock_t	   c_lock;
	struct inode	   vfs_inode;
};

/*
 * coda fs file private data
 */
#define CODA_MAGIC 0xC0DAC0DA
struct coda_file_info {
	int		   cfi_magic;	  /* magic number */
	struct file	  *cfi_container; /* container file for this cnode */
	unsigned int	   cfi_mapcount;  /* nr of times this file is mapped */
};

#define CODA_FTOC(file) ((struct coda_file_info *)((file)->private_data))

/* flags */
#define C_VATTR       0x1   /* Validity of vattr in inode */
#define C_FLUSH       0x2   /* used after a flush */
#define C_DYING       0x4   /* from venus (which died) */
#define C_PURGE       0x8

struct inode *coda_cnode_make(struct CodaFid *, struct super_block *);
struct inode *coda_iget(struct super_block *sb, struct CodaFid *fid, struct coda_vattr *attr);
struct inode *coda_cnode_makectl(struct super_block *sb);
struct inode *coda_fid_to_inode(struct CodaFid *fid, struct super_block *sb);
void coda_replace_fid(struct inode *, struct CodaFid *, struct CodaFid *);

#endif
