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
#ifndef NFS_IDMAP_H
#define NFS_IDMAP_H

#include <uapi/beep/nfs_idmap.h>


/* Forward declaration to make this header independent of others */
struct nfs_client;
struct nfs_server;
struct nfs_fattr;
struct nfs4_string;

#if IS_ENABLED(CONFIG_NFS_V4)
int nfs_idmap_init(void);
void nfs_idmap_quit(void);
#else
static inline int nfs_idmap_init(void)
{
	return 0;
}

static inline void nfs_idmap_quit(void)
{}
#endif

int nfs_idmap_new(struct nfs_client *);
void nfs_idmap_delete(struct nfs_client *);

void nfs_fattr_init_names(struct nfs_fattr *fattr,
		struct nfs4_string *owner_name,
		struct nfs4_string *group_name);
void nfs_fattr_free_names(struct nfs_fattr *);
void nfs_fattr_map_and_free_names(struct nfs_server *, struct nfs_fattr *);

int nfs_map_name_to_uid(const struct nfs_server *, const char *, size_t, __u32 *);
int nfs_map_group_to_gid(const struct nfs_server *, const char *, size_t, __u32 *);
int nfs_map_uid_to_name(const struct nfs_server *, __u32, char *, size_t);
int nfs_map_gid_to_group(const struct nfs_server *, __u32, char *, size_t);

extern unsigned int nfs_idmap_cache_timeout;
#endif /* NFS_IDMAP_H */
