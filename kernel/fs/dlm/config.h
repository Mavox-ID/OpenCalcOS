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
#ifndef __CONFIG_DOT_H__
#define __CONFIG_DOT_H__

struct dlm_config_node {
	int nodeid;
	int weight;
	int new;
	uint32_t comm_seq;
};

#define DLM_MAX_ADDR_COUNT 3

struct dlm_config_info {
	int ci_tcp_port;
	int ci_buffer_size;
	int ci_rsbtbl_size;
	int ci_recover_timer;
	int ci_toss_secs;
	int ci_scan_secs;
	int ci_log_debug;
	int ci_protocol;
	int ci_timewarn_cs;
	int ci_waitwarn_us;
	int ci_new_rsb_count;
	int ci_recover_callbacks;
	char ci_cluster_name[DLM_LOCKSPACE_LEN];
};

extern struct dlm_config_info dlm_config;

int dlm_config_init(void);
void dlm_config_exit(void);
int dlm_config_nodes(char *lsname, struct dlm_config_node **nodes_out,
		     int *count_out);
int dlm_comm_seq(int nodeid, uint32_t *seq);
int dlm_our_nodeid(void);
int dlm_our_addr(struct sockaddr_storage *addr, int num);

#endif				/* __CONFIG_DOT_H__ */

