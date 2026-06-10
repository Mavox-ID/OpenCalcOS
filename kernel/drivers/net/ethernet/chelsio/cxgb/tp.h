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
#ifndef CHELSIO_TP_H
#define CHELSIO_TP_H

#include "common.h"

#define TP_MAX_RX_COALESCING_SIZE 16224U

struct tp_mib_statistics {

	/* IP */
	u32 ipInReceive_hi;
	u32 ipInReceive_lo;
	u32 ipInHdrErrors_hi;
	u32 ipInHdrErrors_lo;
	u32 ipInAddrErrors_hi;
	u32 ipInAddrErrors_lo;
	u32 ipInUnknownProtos_hi;
	u32 ipInUnknownProtos_lo;
	u32 ipInDiscards_hi;
	u32 ipInDiscards_lo;
	u32 ipInDelivers_hi;
	u32 ipInDelivers_lo;
	u32 ipOutRequests_hi;
	u32 ipOutRequests_lo;
	u32 ipOutDiscards_hi;
	u32 ipOutDiscards_lo;
	u32 ipOutNoRoutes_hi;
	u32 ipOutNoRoutes_lo;
	u32 ipReasmTimeout;
	u32 ipReasmReqds;
	u32 ipReasmOKs;
	u32 ipReasmFails;

	u32 reserved[8];

	/* TCP */
	u32 tcpActiveOpens;
	u32 tcpPassiveOpens;
	u32 tcpAttemptFails;
	u32 tcpEstabResets;
	u32 tcpOutRsts;
	u32 tcpCurrEstab;
	u32 tcpInSegs_hi;
	u32 tcpInSegs_lo;
	u32 tcpOutSegs_hi;
	u32 tcpOutSegs_lo;
	u32 tcpRetransSeg_hi;
	u32 tcpRetransSeg_lo;
	u32 tcpInErrs_hi;
	u32 tcpInErrs_lo;
	u32 tcpRtoMin;
	u32 tcpRtoMax;
};

struct petp;
struct tp_params;

struct petp *t1_tp_create(adapter_t *adapter, struct tp_params *p);
void t1_tp_destroy(struct petp *tp);

void t1_tp_intr_disable(struct petp *tp);
void t1_tp_intr_enable(struct petp *tp);
void t1_tp_intr_clear(struct petp *tp);
int t1_tp_intr_handler(struct petp *tp);

void t1_tp_get_mib_statistics(adapter_t *adap, struct tp_mib_statistics *tps);
void t1_tp_set_tcp_checksum_offload(struct petp *tp, int enable);
void t1_tp_set_ip_checksum_offload(struct petp *tp, int enable);
int t1_tp_set_coalescing_size(struct petp *tp, unsigned int size);
int t1_tp_reset(struct petp *tp, struct tp_params *p, unsigned int tp_clk);
#endif
