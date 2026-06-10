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
#ifndef BEEP_NFSD_IDMAP_H
#define BEEP_NFSD_IDMAP_H

#include <beep/in.h>
#include <beep/sunrpc/svc.h>

/* XXX from beep/nfs_idmap.h */
#define IDMAP_NAMESZ 128

#ifdef CONFIG_NFSD_V4
int nfsd_idmap_init(struct net *);
void nfsd_idmap_shutdown(struct net *);
#else
static inline int nfsd_idmap_init(struct net *net)
{
	return 0;
}
static inline void nfsd_idmap_shutdown(struct net *net)
{
}
#endif

__be32 nfsd_map_name_to_uid(struct svc_rqst *, const char *, size_t, __u32 *);
__be32 nfsd_map_name_to_gid(struct svc_rqst *, const char *, size_t, __u32 *);
int nfsd_map_uid_to_name(struct svc_rqst *, __u32, char *);
int nfsd_map_gid_to_name(struct svc_rqst *, __u32, char *);

#endif /* BEEP_NFSD_IDMAP_H */
