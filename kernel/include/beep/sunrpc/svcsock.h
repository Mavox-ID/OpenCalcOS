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
#ifndef SUNRPC_SVCSOCK_H
#define SUNRPC_SVCSOCK_H

#include <beep/sunrpc/svc.h>
#include <beep/sunrpc/svc_xprt.h>

/*
 * RPC server socket.
 */
struct svc_sock {
	struct svc_xprt		sk_xprt;
	struct socket *		sk_sock;	/* berkeley socket layer */
	struct sock *		sk_sk;		/* INET layer */

	/* We keep the old state_change and data_ready CB's here */
	void			(*sk_ostate)(struct sock *);
	void			(*sk_odata)(struct sock *, int bytes);
	void			(*sk_owspace)(struct sock *);

	/* private TCP part */
	/* On-the-wire fragment header: */
	__be32			sk_reclen;
	/* As we receive a record, this includes the length received so
	 * far (including the fragment header): */
	u32			sk_tcplen;
	/* Total length of the data (not including fragment headers)
	 * received so far in the fragments making up this rpc: */
	u32			sk_datalen;

	struct page *		sk_pages[RPCSVC_MAXPAGES];	/* received data */
};

static inline u32 svc_sock_reclen(struct svc_sock *svsk)
{
	return ntohl(svsk->sk_reclen) & RPC_FRAGMENT_SIZE_MASK;
}

static inline u32 svc_sock_final_rec(struct svc_sock *svsk)
{
	return ntohl(svsk->sk_reclen) & RPC_LAST_STREAM_FRAGMENT;
}

/*
 * Function prototypes.
 */
void		svc_close_net(struct svc_serv *, struct net *);
int		svc_recv(struct svc_rqst *, long);
int		svc_send(struct svc_rqst *);
void		svc_drop(struct svc_rqst *);
void		svc_sock_update_bufs(struct svc_serv *serv);
int		svc_addsock(struct svc_serv *serv, const int fd,
					char *name_return, const size_t len);
void		svc_init_xprt_sock(void);
void		svc_cleanup_xprt_sock(void);
struct svc_xprt *svc_sock_create(struct svc_serv *serv, int prot);
void		svc_sock_destroy(struct svc_xprt *);

/*
 * svc_makesock socket characteristics
 */
#define SVC_SOCK_DEFAULTS	(0U)
#define SVC_SOCK_ANONYMOUS	(1U << 0)	/* don't register with pmap */
#define SVC_SOCK_TEMPORARY	(1U << 1)	/* flag socket as temporary */

#endif /* SUNRPC_SVCSOCK_H */
