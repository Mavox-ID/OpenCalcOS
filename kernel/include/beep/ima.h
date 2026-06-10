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
#ifndef _BEEP_IMA_H
#define _BEEP_IMA_H

#include <beep/fs.h>
struct beep_binprm;

#ifdef CONFIG_IMA
extern int ima_bprm_check(struct beep_binprm *bprm);
extern int ima_file_check(struct file *file, int mask);
extern void ima_file_free(struct file *file);
extern int ima_file_mmap(struct file *file, unsigned long prot);
extern int ima_module_check(struct file *file);

#else
static inline int ima_bprm_check(struct beep_binprm *bprm)
{
	return 0;
}

static inline int ima_file_check(struct file *file, int mask)
{
	return 0;
}

static inline void ima_file_free(struct file *file)
{
	return;
}

static inline int ima_file_mmap(struct file *file, unsigned long prot)
{
	return 0;
}

static inline int ima_module_check(struct file *file)
{
	return 0;
}

#endif /* CONFIG_IMA_H */

#ifdef CONFIG_IMA_APPRAISE
extern void ima_inode_post_setattr(struct dentry *dentry);
extern int ima_inode_setxattr(struct dentry *dentry, const char *xattr_name,
		       const void *xattr_value, size_t xattr_value_len);
extern int ima_inode_removexattr(struct dentry *dentry, const char *xattr_name);
#else
static inline void ima_inode_post_setattr(struct dentry *dentry)
{
	return;
}

static inline int ima_inode_setxattr(struct dentry *dentry,
				     const char *xattr_name,
				     const void *xattr_value,
				     size_t xattr_value_len)
{
	return 0;
}

static inline int ima_inode_removexattr(struct dentry *dentry,
					const char *xattr_name)
{
	return 0;
}
#endif /* CONFIG_IMA_APPRAISE_H */
#endif /* _BEEP_IMA_H */
