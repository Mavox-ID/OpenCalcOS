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
#include <beep/percpu.h>
#include <beep/seq_file.h>
#include <beep/proc_fs.h>

#include "rds.h"
#include "ib.h"

DEFINE_PER_CPU_SHARED_ALIGNED(struct rds_ib_statistics, rds_ib_stats);

static const char *const rds_ib_stat_names[] = {
	"ib_connect_raced",
	"ib_listen_closed_stale",
	"ib_tx_cq_call",
	"ib_tx_cq_event",
	"ib_tx_ring_full",
	"ib_tx_throttle",
	"ib_tx_sg_mapping_failure",
	"ib_tx_stalled",
	"ib_tx_credit_updates",
	"ib_rx_cq_call",
	"ib_rx_cq_event",
	"ib_rx_ring_empty",
	"ib_rx_refill_from_cq",
	"ib_rx_refill_from_thread",
	"ib_rx_alloc_limit",
	"ib_rx_credit_updates",
	"ib_ack_sent",
	"ib_ack_send_failure",
	"ib_ack_send_delayed",
	"ib_ack_send_piggybacked",
	"ib_ack_received",
	"ib_rdma_mr_alloc",
	"ib_rdma_mr_free",
	"ib_rdma_mr_used",
	"ib_rdma_mr_pool_flush",
	"ib_rdma_mr_pool_wait",
	"ib_rdma_mr_pool_depleted",
	"ib_atomic_cswp",
	"ib_atomic_fadd",
};

unsigned int rds_ib_stats_info_copy(struct rds_info_iterator *iter,
				    unsigned int avail)
{
	struct rds_ib_statistics stats = {0, };
	uint64_t *src;
	uint64_t *sum;
	size_t i;
	int cpu;

	if (avail < ARRAY_SIZE(rds_ib_stat_names))
		goto out;

	for_each_online_cpu(cpu) {
		src = (uint64_t *)&(per_cpu(rds_ib_stats, cpu));
		sum = (uint64_t *)&stats;
		for (i = 0; i < sizeof(stats) / sizeof(uint64_t); i++)
			*(sum++) += *(src++);
	}

	rds_stats_info_copy(iter, (uint64_t *)&stats, rds_ib_stat_names,
			    ARRAY_SIZE(rds_ib_stat_names));
out:
	return ARRAY_SIZE(rds_ib_stat_names);
}
