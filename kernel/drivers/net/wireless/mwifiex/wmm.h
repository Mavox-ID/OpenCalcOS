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
#ifndef _MWIFIEX_WMM_H_
#define _MWIFIEX_WMM_H_

enum ieee_types_wmm_aciaifsn_bitmasks {
	MWIFIEX_AIFSN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ACM = BIT(4),
	MWIFIEX_ACI = (BIT(5) | BIT(6)),
};

enum ieee_types_wmm_ecw_bitmasks {
	MWIFIEX_ECW_MIN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ECW_MAX = (BIT(4) | BIT(5) | BIT(6) | BIT(7)),
};

static const u16 mwifiex_1d_to_wmm_queue[8] = { 1, 0, 0, 1, 2, 2, 3, 3 };

/*
 * This function retrieves the TID of the given RA list.
 */
static inline int
mwifiex_get_tid(struct mwifiex_ra_list_tbl *ptr)
{
	struct sk_buff *skb;

	if (skb_queue_empty(&ptr->skb_head))
		return 0;

	skb = skb_peek(&ptr->skb_head);

	return skb->priority;
}

/*
 * This function gets the length of a list.
 */
static inline int
mwifiex_wmm_list_len(struct list_head *head)
{
	struct list_head *pos;
	int count = 0;

	list_for_each(pos, head)
		++count;

	return count;
}

/*
 * This function checks if a RA list is empty or not.
 */
static inline u8
mwifiex_wmm_is_ra_list_empty(struct list_head *ra_list_hhead)
{
	struct mwifiex_ra_list_tbl *ra_list;
	int is_list_empty;

	list_for_each_entry(ra_list, ra_list_hhead, list) {
		is_list_empty = skb_queue_empty(&ra_list->skb_head);
		if (!is_list_empty)
			return false;
	}

	return true;
}

void mwifiex_wmm_add_buf_txqueue(struct mwifiex_private *priv,
					struct sk_buff *skb);
void mwifiex_ralist_add(struct mwifiex_private *priv, u8 *ra);

int mwifiex_wmm_lists_empty(struct mwifiex_adapter *adapter);
void mwifiex_wmm_process_tx(struct mwifiex_adapter *adapter);
int mwifiex_is_ralist_valid(struct mwifiex_private *priv,
			    struct mwifiex_ra_list_tbl *ra_list, int tid);

u8 mwifiex_wmm_compute_drv_pkt_delay(struct mwifiex_private *priv,
					     const struct sk_buff *skb);
void mwifiex_wmm_init(struct mwifiex_adapter *adapter);

extern u32 mwifiex_wmm_process_association_req(struct mwifiex_private *priv,
						 u8 **assoc_buf,
						 struct ieee_types_wmm_parameter
						 *wmmie,
						 struct ieee80211_ht_cap
						 *htcap);

void mwifiex_wmm_setup_queue_priorities(struct mwifiex_private *priv,
					struct ieee_types_wmm_parameter
					*wmm_ie);
void mwifiex_wmm_setup_ac_downgrade(struct mwifiex_private *priv);
extern int mwifiex_ret_wmm_get_status(struct mwifiex_private *priv,
				      const struct host_cmd_ds_command *resp);

#endif /* !_MWIFIEX_WMM_H_ */
