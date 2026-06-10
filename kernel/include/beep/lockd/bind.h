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
#ifndef BEEP_LOCKD_BIND_H
#define BEEP_LOCKD_BIND_H

#include <beep/lockd/nlm.h>
/* need xdr-encoded error codes too, so... */
#include <beep/lockd/xdr.h>
#ifdef CONFIG_LOCKD_V4
#include <beep/lockd/xdr4.h>
#endif

/* Dummy declarations */
struct svc_rqst;

/*
 * This is the set of functions for lockd->nfsd communication
 */
struct nlmsvc_binding {
	__be32			(*fopen)(struct svc_rqst *,
						struct nfs_fh *,
						struct file **);
	void			(*fclose)(struct file *);
};

extern struct nlmsvc_binding *	nlmsvc_ops;

/*
 * Similar to nfs_client_initdata, but without the NFS-specific
 * rpc_ops field.
 */
struct nlmclnt_initdata {
	const char		*hostname;
	const struct sockaddr	*address;
	size_t			addrlen;
	unsigned short		protocol;
	u32			nfs_version;
	int			noresvport;
	struct net		*net;
};

/*
 * Functions exported by the lockd module
 */

extern struct nlm_host *nlmclnt_init(const struct nlmclnt_initdata *nlm_init);
extern void	nlmclnt_done(struct nlm_host *host);

extern int	nlmclnt_proc(struct nlm_host *host, int cmd,
					struct file_lock *fl);
extern int	lockd_up(struct net *net);
extern void	lockd_down(struct net *net);

#endif /* BEEP_LOCKD_BIND_H */
