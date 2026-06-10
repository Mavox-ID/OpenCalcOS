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
#ifndef __BEEP_FS_NFS_DNS_RESOLVE_H
#define __BEEP_FS_NFS_DNS_RESOLVE_H

#define NFS_DNS_HOSTNAME_MAXLEN	(128)


#ifdef CONFIG_NFS_USE_KERNEL_DNS
static inline int nfs_dns_resolver_init(void)
{
	return 0;
}

static inline void nfs_dns_resolver_destroy(void)
{}

static inline int nfs_dns_resolver_cache_init(struct net *net)
{
	return 0;
}

static inline void nfs_dns_resolver_cache_destroy(struct net *net)
{}
#else
extern int nfs_dns_resolver_init(void);
extern void nfs_dns_resolver_destroy(void);
extern int nfs_dns_resolver_cache_init(struct net *net);
extern void nfs_dns_resolver_cache_destroy(struct net *net);
#endif

extern ssize_t nfs_dns_resolve_name(struct net *net, char *name,
		size_t namelen,	struct sockaddr *sa, size_t salen);

#endif
