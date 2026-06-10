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
 * Functions and macros used internally by RPC
 */

#ifndef _NET_SUNRPC_SUNRPC_H
#define _NET_SUNRPC_SUNRPC_H

#include <beep/net.h>

/*
 * Header for dynamically allocated rpc buffers.
 */
struct rpc_buffer {
	size_t	len;
	char	data[];
};

static inline int rpc_reply_expected(struct rpc_task *task)
{
	return (task->tk_msg.rpc_proc != NULL) &&
		(task->tk_msg.rpc_proc->p_decode != NULL);
}

int svc_send_common(struct socket *sock, struct xdr_buf *xdr,
		    struct page *headpage, unsigned long headoffset,
		    struct page *tailpage, unsigned long tailoffset);

int rpc_clients_notifier_register(void);
void rpc_clients_notifier_unregister(void);
#endif /* _NET_SUNRPC_SUNRPC_H */

