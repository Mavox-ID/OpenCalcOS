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
#ifndef _BEEP_SUNRPC_METRICS_H
#define _BEEP_SUNRPC_METRICS_H

#include <beep/seq_file.h>
#include <beep/ktime.h>

#define RPC_IOSTATS_VERS	"1.0"

struct rpc_iostats {
	/*
	 * These counters give an idea about how many request
	 * transmissions are required, on average, to complete that
	 * particular procedure.  Some procedures may require more
	 * than one transmission because the server is unresponsive,
	 * the client is retransmitting too aggressively, or the
	 * requests are large and the network is congested.
	 */
	unsigned long		om_ops,		/* count of operations */
				om_ntrans,	/* count of RPC transmissions */
				om_timeouts;	/* count of major timeouts */

	/*
	 * These count how many bytes are sent and received for a
	 * given RPC procedure type.  This indicates how much load a
	 * particular procedure is putting on the network.  These
	 * counts include the RPC and ULP headers, and the request
	 * payload.
	 */
	unsigned long long      om_bytes_sent,	/* count of bytes out */
				om_bytes_recv;	/* count of bytes in */

	/*
	 * The length of time an RPC request waits in queue before
	 * transmission, the network + server latency of the request,
	 * and the total time the request spent from init to release
	 * are measured.
	 */
	ktime_t			om_queue,	/* queued for xmit */
				om_rtt,		/* RPC RTT */
				om_execute;	/* RPC execution */
} ____cacheline_aligned;

struct rpc_task;
struct rpc_clnt;

/*
 * EXPORTed functions for managing rpc_iostats structures
 */

#ifdef CONFIG_PROC_FS

struct rpc_iostats *	rpc_alloc_iostats(struct rpc_clnt *);
void			rpc_count_iostats(const struct rpc_task *,
					  struct rpc_iostats *);
void			rpc_print_iostats(struct seq_file *, struct rpc_clnt *);
void			rpc_free_iostats(struct rpc_iostats *);

#else  /*  CONFIG_PROC_FS  */

static inline struct rpc_iostats *rpc_alloc_iostats(struct rpc_clnt *clnt) { return NULL; }
static inline void rpc_count_iostats(const struct rpc_task *task,
				     struct rpc_iostats *stats) {}
static inline void rpc_print_iostats(struct seq_file *seq, struct rpc_clnt *clnt) {}
static inline void rpc_free_iostats(struct rpc_iostats *stats) {}

#endif  /*  CONFIG_PROC_FS  */

#endif /* _BEEP_SUNRPC_METRICS_H */
