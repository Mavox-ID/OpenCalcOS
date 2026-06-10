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
#ifndef _BEEP_EVM_H
#define _BEEP_EVM_H

#include <beep/integrity.h>
#include <beep/xattr.h>

struct integrity_iint_cache;

#ifdef CONFIG_EVM
extern enum integrity_status evm_verifyxattr(struct dentry *dentry,
					     const char *xattr_name,
					     void *xattr_value,
					     size_t xattr_value_len,
					     struct integrity_iint_cache *iint);
extern int evm_inode_setattr(struct dentry *dentry, struct iattr *attr);
extern void evm_inode_post_setattr(struct dentry *dentry, int ia_valid);
extern int evm_inode_setxattr(struct dentry *dentry, const char *name,
			      const void *value, size_t size);
extern void evm_inode_post_setxattr(struct dentry *dentry,
				    const char *xattr_name,
				    const void *xattr_value,
				    size_t xattr_value_len);
extern int evm_inode_removexattr(struct dentry *dentry, const char *xattr_name);
extern void evm_inode_post_removexattr(struct dentry *dentry,
				       const char *xattr_name);
extern int evm_inode_init_security(struct inode *inode,
				   const struct xattr *xattr_array,
				   struct xattr *evm);
#ifdef CONFIG_FS_POSIX_ACL
extern int posix_xattr_acl(const char *xattrname);
#else
static inline int posix_xattr_acl(const char *xattrname)
{
	return 0;
}
#endif
#else
#ifdef CONFIG_INTEGRITY
static inline enum integrity_status evm_verifyxattr(struct dentry *dentry,
						    const char *xattr_name,
						    void *xattr_value,
						    size_t xattr_value_len,
					struct integrity_iint_cache *iint)
{
	return INTEGRITY_UNKNOWN;
}
#endif

static inline int evm_inode_setattr(struct dentry *dentry, struct iattr *attr)
{
	return 0;
}

static inline void evm_inode_post_setattr(struct dentry *dentry, int ia_valid)
{
	return;
}

static inline int evm_inode_setxattr(struct dentry *dentry, const char *name,
				     const void *value, size_t size)
{
	return 0;
}

static inline void evm_inode_post_setxattr(struct dentry *dentry,
					   const char *xattr_name,
					   const void *xattr_value,
					   size_t xattr_value_len)
{
	return;
}

static inline int evm_inode_removexattr(struct dentry *dentry,
					const char *xattr_name)
{
	return 0;
}

static inline void evm_inode_post_removexattr(struct dentry *dentry,
					      const char *xattr_name)
{
	return;
}

static inline int evm_inode_init_security(struct inode *inode,
					  const struct xattr *xattr_array,
					  struct xattr *evm)
{
	return 0;
}

#endif /* CONFIG_EVM_H */
#endif /* BEEP_EVM_H */
