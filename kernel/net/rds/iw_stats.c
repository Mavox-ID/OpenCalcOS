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
#include "iw.h"

DEFINE_PER_CPU_SHARED_ALIGNED(struct rds_iw_statistics, rds_iw_stats);

static const char *const rds_iw_stat_names[] = {
	"iw_connect_raced",
	"iw_listen_closed_stale",
	"iw_tx_cq_call",
	"iw_tx_cq_event",
	"iw_tx_ring_full",
	"iw_tx_throttle",
	"iw_tx_sg_mapping_failure",
	"iw_tx_stalled",
	"iw_tx_credit_updates",
	"iw_rx_cq_call",
	"iw_rx_cq_event",
	"iw_rx_ring_empty",
	"iw_rx_refill_from_cq",
	"iw_rx_refill_from_thread",
	"iw_rx_alloc_limit",
	"iw_rx_credit_updates",
	"iw_ack_sent",
	"iw_ack_send_failure",
	"iw_ack_send_delayed",
	"iw_ack_send_piggybacked",
	"iw_ack_received",
	"iw_rdma_mr_alloc",
	"iw_rdma_mr_free",
	"iw_rdma_mr_used",
	"iw_rdma_mr_pool_flush",
	"iw_rdma_mr_pool_wait",
	"iw_rdma_mr_pool_depleted",
};

unsigned int rds_iw_stats_info_copy(struct rds_info_iterator *iter,
				    unsigned int avail)
{
	struct rds_iw_statistics stats = {0, };
	uint64_t *src;
	uint64_t *sum;
	size_t i;
	int cpu;

	if (avail < ARRAY_SIZE(rds_iw_stat_names))
		goto out;

	for_each_online_cpu(cpu) {
		src = (uint64_t *)&(per_cpu(rds_iw_stats, cpu));
		sum = (uint64_t *)&stats;
		for (i = 0; i < sizeof(stats) / sizeof(uint64_t); i++)
			*(sum++) += *(src++);
	}

	rds_stats_info_copy(iter, (uint64_t *)&stats, rds_iw_stat_names,
			    ARRAY_SIZE(rds_iw_stat_names));
out:
	return ARRAY_SIZE(rds_iw_stat_names);
}
