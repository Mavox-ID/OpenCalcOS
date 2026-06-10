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
#ifndef BEEP_NFS4_ACL_H
#define BEEP_NFS4_ACL_H

#include <beep/posix_acl.h>

/* Maximum ACL we'll accept from client; chosen (somewhat arbitrarily) to
 * fit in a page: */
#define NFS4_ACL_MAX 170

struct nfs4_acl *nfs4_acl_new(int);
int nfs4_acl_get_whotype(char *, u32);
int nfs4_acl_write_who(int who, char *p);
int nfs4_acl_permission(struct nfs4_acl *acl, uid_t owner, gid_t group,
		                        uid_t who, u32 mask);

#define NFS4_ACL_TYPE_DEFAULT	0x01
#define NFS4_ACL_DIR		0x02
#define NFS4_ACL_OWNER		0x04

struct nfs4_acl *nfs4_acl_posix_to_nfsv4(struct posix_acl *,
				struct posix_acl *, unsigned int flags);
int nfs4_acl_nfsv4_to_posix(struct nfs4_acl *, struct posix_acl **,
				struct posix_acl **, unsigned int flags);

#endif /* BEEP_NFS4_ACL_H */
