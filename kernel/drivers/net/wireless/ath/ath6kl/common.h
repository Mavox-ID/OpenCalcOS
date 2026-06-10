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
#ifndef COMMON_H
#define COMMON_H

#include <beep/netdevice.h>

#define ATH6KL_MAX_IE			256

extern __printf(2, 3)
int ath6kl_printk(const char *level, const char *fmt, ...);

/*
 * Reflects the version of binary interface exposed by ATH6KL target
 * firmware. Needs to be incremented by 1 for any change in the firmware
 * that requires upgrade of the driver on the host side for the change to
 * work correctly
 */
#define ATH6KL_ABI_VERSION        1

#define SIGNAL_QUALITY_METRICS_NUM_MAX    2

enum {
	SIGNAL_QUALITY_METRICS_SNR = 0,
	SIGNAL_QUALITY_METRICS_RSSI,
	SIGNAL_QUALITY_METRICS_ALL,
};

/*
 * Data Path
 */

#define WMI_MAX_TX_DATA_FRAME_LENGTH	      \
	(1500 + sizeof(struct wmi_data_hdr) + \
	 sizeof(struct ethhdr) +      \
	 sizeof(struct ath6kl_llc_snap_hdr))

/* An AMSDU frame */ /* The MAX AMSDU length of AR6003 is 3839 */
#define WMI_MAX_AMSDU_RX_DATA_FRAME_LENGTH    \
	(3840 + sizeof(struct wmi_data_hdr) + \
	 sizeof(struct ethhdr) +      \
	 sizeof(struct ath6kl_llc_snap_hdr))

#define EPPING_ALIGNMENT_PAD			       \
	(((sizeof(struct htc_frame_hdr) + 3) & (~0x3)) \
	 - sizeof(struct htc_frame_hdr))

struct ath6kl_llc_snap_hdr {
	u8 dsap;
	u8 ssap;
	u8 cntl;
	u8 org_code[3];
	__be16 eth_type;
} __packed;

enum crypto_type {
	NONE_CRYPT          = 0x01,
	WEP_CRYPT           = 0x02,
	TKIP_CRYPT          = 0x04,
	AES_CRYPT           = 0x08,
	WAPI_CRYPT          = 0x10,
};

struct htc_endpoint_credit_dist;
struct ath6kl;
struct ath6kl_htcap;
enum htc_credit_dist_reason;
struct ath6kl_htc_credit_info;

struct sk_buff *ath6kl_buf_alloc(int size);
#endif /* COMMON_H */
