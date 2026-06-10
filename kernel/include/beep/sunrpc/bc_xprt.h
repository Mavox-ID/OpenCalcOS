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
/*
 * Functions to create and manage the backchannel
 */

#ifndef _BEEP_SUNRPC_BC_XPRT_H
#define _BEEP_SUNRPC_BC_XPRT_H

#include <beep/sunrpc/svcsock.h>
#include <beep/sunrpc/xprt.h>
#include <beep/sunrpc/sched.h>

#ifdef CONFIG_SUNRPC_BACKCHANNEL
struct rpc_rqst *xprt_alloc_bc_request(struct rpc_xprt *xprt);
void xprt_free_bc_request(struct rpc_rqst *req);
int xprt_setup_backchannel(struct rpc_xprt *, unsigned int min_reqs);
void xprt_destroy_backchannel(struct rpc_xprt *, unsigned int max_reqs);
int bc_send(struct rpc_rqst *req);

/*
 * Determine if a shared backchannel is in use
 */
static inline int svc_is_backchannel(const struct svc_rqst *rqstp)
{
	if (rqstp->rq_server->sv_bc_xprt)
		return 1;
	return 0;
}
#else /* CONFIG_SUNRPC_BACKCHANNEL */
static inline int xprt_setup_backchannel(struct rpc_xprt *xprt,
					 unsigned int min_reqs)
{
	return 0;
}

static inline int svc_is_backchannel(const struct svc_rqst *rqstp)
{
	return 0;
}

static inline void xprt_free_bc_request(struct rpc_rqst *req)
{
}
#endif /* CONFIG_SUNRPC_BACKCHANNEL */
#endif /* _BEEP_SUNRPC_BC_XPRT_H */

