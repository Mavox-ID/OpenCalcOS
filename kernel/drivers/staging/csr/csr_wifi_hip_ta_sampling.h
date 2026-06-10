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
 * ---------------------------------------------------------------------------
 *  FILE:     csr_wifi_hip_ta_sampling.h
 *
 *  PURPOSE:
 *      This file contains Traffic Analysis definitions common to the
 *      sampling and analysis modules.
 *
 * ---------------------------------------------------------------------------
 */
#ifndef __TA_SAMPLING_H__
#define __TA_SAMPLING_H__

#include "csr_wifi_hip_unifi.h"

typedef struct ta_l4stats
{
    u32 rxTcpBytesCount;
    u32 txTcpBytesCount;
    u32 rxUdpBytesCount;
    u32 txUdpBytesCount;
} ta_l4stats_t;

/*
 * Context structure to preserve state between calls.
 */

typedef struct ta_data
{
    /* Current packet filter configuration */
    u16 packet_filter;

    /* Current packet custom filter configuration */
    CsrWifiRouterCtrlTrafficFilter custom_filter;

    /* The timestamp of the last tx packet processed. */
    u32 tx_last_ts;

    /* The timestamp of the last packet processed. */
    u32 last_indication_time;

    /* Statistics */
    CsrWifiRouterCtrlTrafficStats stats;

    /* Current traffic classification */
    CsrWifiRouterCtrlTrafficType traffic_type;

    /* Sum of packet rx rates for this interval used to calculate mean */
    u32    rx_sum_rate;
    ta_l4stats_t ta_l4stats;
} ta_data_t;


void unifi_ta_sampling_init(card_t *card);

#endif /* __TA_SAMPLING_H__ */
