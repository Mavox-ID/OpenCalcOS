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
#ifndef __BEEP_INTERNAL_NFS_H
#define __BEEP_INTERNAL_NFS_H

#include <beep/fs.h>
#include <beep/sunrpc/sched.h>
#include <beep/nfs_xdr.h>

struct nfs_subversion {
	struct module *owner;	/* THIS_MODULE pointer */
	struct file_system_type *nfs_fs;	/* NFS filesystem type */
	const struct rpc_version *rpc_vers;	/* NFS version information */
	const struct nfs_rpc_ops *rpc_ops;	/* NFS operations */
	const struct super_operations *sops;	/* NFS Super operations */
	const struct xattr_handler **xattr;	/* NFS xattr handlers */
	struct list_head list;		/* List of NFS versions */
};

struct nfs_subversion *get_nfs_version(unsigned int);
void put_nfs_version(struct nfs_subversion *);
void register_nfs_version(struct nfs_subversion *);
void unregister_nfs_version(struct nfs_subversion *);

#endif /* __BEEP_INTERNAL_NFS_H */
