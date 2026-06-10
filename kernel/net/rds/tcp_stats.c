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
#include "tcp.h"

DEFINE_PER_CPU(struct rds_tcp_statistics, rds_tcp_stats)
	____cacheline_aligned;

static const char * const rds_tcp_stat_names[] = {
	"tcp_data_ready_calls",
	"tcp_write_space_calls",
	"tcp_sndbuf_full",
	"tcp_connect_raced",
	"tcp_listen_closed_stale",
};

unsigned int rds_tcp_stats_info_copy(struct rds_info_iterator *iter,
				     unsigned int avail)
{
	struct rds_tcp_statistics stats = {0, };
	uint64_t *src;
	uint64_t *sum;
	size_t i;
	int cpu;

	if (avail < ARRAY_SIZE(rds_tcp_stat_names))
		goto out;

	for_each_online_cpu(cpu) {
		src = (uint64_t *)&(per_cpu(rds_tcp_stats, cpu));
		sum = (uint64_t *)&stats;
		for (i = 0; i < sizeof(stats) / sizeof(uint64_t); i++)
			*(sum++) += *(src++);
	}

	rds_stats_info_copy(iter, (uint64_t *)&stats, rds_tcp_stat_names,
			    ARRAY_SIZE(rds_tcp_stat_names));
out:
	return ARRAY_SIZE(rds_tcp_stat_names);
}
