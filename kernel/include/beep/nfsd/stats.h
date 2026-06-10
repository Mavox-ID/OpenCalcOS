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
#ifndef BEEP_NFSD_STATS_H
#define BEEP_NFSD_STATS_H

#include <uapi/beep/nfsd/stats.h>


struct nfsd_stats {
	unsigned int	rchits;		/* repcache hits */
	unsigned int	rcmisses;	/* repcache hits */
	unsigned int	rcnocache;	/* uncached reqs */
	unsigned int	fh_stale;	/* FH stale error */
	unsigned int	fh_lookup;	/* dentry cached */
	unsigned int	fh_anon;	/* anon file dentry returned */
	unsigned int	fh_nocache_dir;	/* filehandle not found in dcache */
	unsigned int	fh_nocache_nondir;	/* filehandle not found in dcache */
	unsigned int	io_read;	/* bytes returned to read requests */
	unsigned int	io_write;	/* bytes passed in write requests */
	unsigned int	th_cnt;		/* number of available threads */
	unsigned int	th_usage[10];	/* number of ticks during which n perdeciles
					 * of available threads were in use */
	unsigned int	th_fullcnt;	/* number of times last free thread was used */
	unsigned int	ra_size;	/* size of ra cache */
	unsigned int	ra_depth[11];	/* number of times ra entry was found that deep
					 * in the cache (10percentiles). [10] = not found */
#ifdef CONFIG_NFSD_V4
	unsigned int	nfs4_opcount[LAST_NFS4_OP + 1];	/* count of individual nfsv4 operations */
#endif

};


extern struct nfsd_stats	nfsdstats;
extern struct svc_stat		nfsd_svcstats;

void	nfsd_stat_init(void);
void	nfsd_stat_shutdown(void);

#endif /* BEEP_NFSD_STATS_H */
