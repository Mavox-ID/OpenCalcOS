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
#include <beep/kernel.h>
#include <beep/slab.h>
#include <beep/in.h>

#include "rds.h"
#include "loop.h"

static DEFINE_SPINLOCK(loop_conns_lock);
static LIST_HEAD(loop_conns);

/*
 * This 'loopback' transport is a special case for flows that originate
 * and terminate on the same machine.
 *
 * Connection build-up notices if the destination address is thought of
 * as a local address by a transport.  At that time it decides to use the
 * loopback transport instead of the bound transport of the sending socket.
 *
 * The loopback transport's sending path just hands the sent rds_message
 * straight to the receiving path via an embedded rds_incoming.
 */

/*
 * Usually a message transits both the sender and receiver's conns as it
 * flows to the receiver.  In the loopback case, though, the receive path
 * is handed the sending conn so the sense of the addresses is reversed.
 */
static int rds_loop_xmit(struct rds_connection *conn, struct rds_message *rm,
			 unsigned int hdr_off, unsigned int sg,
			 unsigned int off)
{
	struct scatterlist *sgp = &rm->data.op_sg[sg];
	int ret = sizeof(struct rds_header) +
			be32_to_cpu(rm->m_inc.i_hdr.h_len);

	/* Do not send cong updates to loopback */
	if (rm->m_inc.i_hdr.h_flags & RDS_FLAG_CONG_BITMAP) {
		rds_cong_map_updated(conn->c_fcong, ~(u64) 0);
		ret = min_t(int, ret, sgp->length - conn->c_xmit_data_off);
		goto out;
	}

	BUG_ON(hdr_off || sg || off);

	rds_inc_init(&rm->m_inc, conn, conn->c_laddr);
	/* For the embedded inc. Matching put is in loop_inc_free() */
	rds_message_addref(rm);

	rds_recv_incoming(conn, conn->c_laddr, conn->c_faddr, &rm->m_inc,
			  GFP_KERNEL);

	rds_send_drop_acked(conn, be64_to_cpu(rm->m_inc.i_hdr.h_sequence),
			    NULL);

	rds_inc_put(&rm->m_inc);
out:
	return ret;
}

/*
 * See rds_loop_xmit(). Since our inc is embedded in the rm, we
 * make sure the rm lives at least until the inc is done.
 */
static void rds_loop_inc_free(struct rds_incoming *inc)
{
        struct rds_message *rm = container_of(inc, struct rds_message, m_inc);
        rds_message_put(rm);
}

/* we need to at least give the thread something to succeed */
static int rds_loop_recv(struct rds_connection *conn)
{
	return 0;
}

struct rds_loop_connection {
	struct list_head loop_node;
	struct rds_connection *conn;
};

/*
 * Even the loopback transport needs to keep track of its connections,
 * so it can call rds_conn_destroy() on them on exit. N.B. there are
 * 1+ loopback addresses (127.*.*.*) so it's not a bug to have
 * multiple loopback conns allocated, although rather useless.
 */
static int rds_loop_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_loop_connection *lc;
	unsigned long flags;

	lc = kzalloc(sizeof(struct rds_loop_connection), gfp);
	if (!lc)
		return -ENOMEM;

	INIT_LIST_HEAD(&lc->loop_node);
	lc->conn = conn;
	conn->c_transport_data = lc;

	spin_lock_irqsave(&loop_conns_lock, flags);
	list_add_tail(&lc->loop_node, &loop_conns);
	spin_unlock_irqrestore(&loop_conns_lock, flags);

	return 0;
}

static void rds_loop_conn_free(void *arg)
{
	struct rds_loop_connection *lc = arg;
	unsigned long flags;

	rdsdebug("lc %p\n", lc);
	spin_lock_irqsave(&loop_conns_lock, flags);
	list_del(&lc->loop_node);
	spin_unlock_irqrestore(&loop_conns_lock, flags);
	kfree(lc);
}

static int rds_loop_conn_connect(struct rds_connection *conn)
{
	rds_connect_complete(conn);
	return 0;
}

static void rds_loop_conn_shutdown(struct rds_connection *conn)
{
}

void rds_loop_exit(void)
{
	struct rds_loop_connection *lc, *_lc;
	LIST_HEAD(tmp_list);

	/* avoid calling conn_destroy with irqs off */
	spin_lock_irq(&loop_conns_lock);
	list_splice(&loop_conns, &tmp_list);
	INIT_LIST_HEAD(&loop_conns);
	spin_unlock_irq(&loop_conns_lock);

	list_for_each_entry_safe(lc, _lc, &tmp_list, loop_node) {
		WARN_ON(lc->conn->c_passive);
		rds_conn_destroy(lc->conn);
	}
}

/*
 * This is missing .xmit_* because loop doesn't go through generic
 * rds_send_xmit() and doesn't call rds_recv_incoming().  .listen_stop and
 * .laddr_check are missing because transport.c doesn't iterate over
 * rds_loop_transport.
 */
struct rds_transport rds_loop_transport = {
	.xmit			= rds_loop_xmit,
	.recv			= rds_loop_recv,
	.conn_alloc		= rds_loop_conn_alloc,
	.conn_free		= rds_loop_conn_free,
	.conn_connect		= rds_loop_conn_connect,
	.conn_shutdown		= rds_loop_conn_shutdown,
	.inc_copy_to_user	= rds_message_inc_copy_to_user,
	.inc_free		= rds_loop_inc_free,
	.t_name			= "loopback",
};
