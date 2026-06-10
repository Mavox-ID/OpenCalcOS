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
#ifndef _NFS_IOSTAT
#define _NFS_IOSTAT

#include <beep/percpu.h>
#include <beep/cache.h>
#include <beep/nfs_iostat.h>

struct nfs_iostats {
	unsigned long long	bytes[__NFSIOS_BYTESMAX];
#ifdef CONFIG_NFS_FSCACHE
	unsigned long long	fscache[__NFSIOS_FSCACHEMAX];
#endif
	unsigned long		events[__NFSIOS_COUNTSMAX];
} ____cacheline_aligned;

static inline void nfs_inc_server_stats(const struct nfs_server *server,
					enum nfs_stat_eventcounters stat)
{
	this_cpu_inc(server->io_stats->events[stat]);
}

static inline void nfs_inc_stats(const struct inode *inode,
				 enum nfs_stat_eventcounters stat)
{
	nfs_inc_server_stats(NFS_SERVER(inode), stat);
}

static inline void nfs_add_server_stats(const struct nfs_server *server,
					enum nfs_stat_bytecounters stat,
					long addend)
{
	this_cpu_add(server->io_stats->bytes[stat], addend);
}

static inline void nfs_add_stats(const struct inode *inode,
				 enum nfs_stat_bytecounters stat,
				 long addend)
{
	nfs_add_server_stats(NFS_SERVER(inode), stat, addend);
}

#ifdef CONFIG_NFS_FSCACHE
static inline void nfs_add_fscache_stats(struct inode *inode,
					 enum nfs_stat_fscachecounters stat,
					 long addend)
{
	this_cpu_add(NFS_SERVER(inode)->io_stats->fscache[stat], addend);
}
#endif

static inline struct nfs_iostats __percpu *nfs_alloc_iostats(void)
{
	return alloc_percpu(struct nfs_iostats);
}

static inline void nfs_free_iostats(struct nfs_iostats __percpu *stats)
{
	if (stats != NULL)
		free_percpu(stats);
}

#endif /* _NFS_IOSTAT */
