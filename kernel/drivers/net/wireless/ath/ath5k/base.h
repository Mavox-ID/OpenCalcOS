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
 * Definitions for the Atheros Wireless LAN controller driver.
 */
#ifndef _DEV_ATH5K_BASE_H
#define _DEV_ATH5K_BASE_H

struct ieee80211_vif;
struct ieee80211_hw;
struct ath5k_hw;
struct ath5k_txq;
struct ieee80211_channel;
struct ath_bus_ops;
enum nl80211_iftype;

enum ath5k_srev_type {
	AR5K_VERSION_MAC,
	AR5K_VERSION_RAD,
};

struct ath5k_srev_name {
	const char		*sr_name;
	enum ath5k_srev_type	sr_type;
	u_int			sr_val;
};

struct ath5k_buf {
	struct list_head	list;
	struct ath5k_desc	*desc;	/* virtual addr of desc */
	dma_addr_t		daddr;	/* physical addr of desc */
	struct sk_buff		*skb;	/* skbuff for buf */
	dma_addr_t		skbaddr;/* physical addr of skb data */
};

struct ath5k_vif {
	bool			assoc; /* are we associated or not */
	enum nl80211_iftype	opmode;
	int			bslot;
	struct ath5k_buf	*bbuf; /* beacon buffer */
};

struct ath5k_vif_iter_data {
	const u8	*hw_macaddr;
	u8		mask[ETH_ALEN];
	u8		active_mac[ETH_ALEN]; /* first active MAC */
	bool		need_set_hw_addr;
	bool		found_active;
	bool		any_assoc;
	enum nl80211_iftype opmode;
	int n_stas;
};

void ath5k_vif_iter(void *data, u8 *mac, struct ieee80211_vif *vif);
bool ath5k_any_vif_assoc(struct ath5k_hw *ah);

int ath5k_start(struct ieee80211_hw *hw);
void ath5k_stop(struct ieee80211_hw *hw);

void ath5k_beacon_update_timers(struct ath5k_hw *ah, u64 bc_tsf);
int ath5k_beacon_update(struct ieee80211_hw *hw, struct ieee80211_vif *vif);
void ath5k_beacon_config(struct ath5k_hw *ah);
void ath5k_set_beacon_filter(struct ieee80211_hw *hw, bool enable);

void ath5k_update_bssid_mask_and_opmode(struct ath5k_hw *ah,
					struct ieee80211_vif *vif);
int ath5k_chan_set(struct ath5k_hw *ah, struct ieee80211_channel *chan);
void ath5k_txbuf_free_skb(struct ath5k_hw *ah, struct ath5k_buf *bf);
void ath5k_rxbuf_free_skb(struct ath5k_hw *ah, struct ath5k_buf *bf);
void ath5k_tx_queue(struct ieee80211_hw *hw, struct sk_buff *skb,
		    struct ath5k_txq *txq);

const char *ath5k_chip_name(enum ath5k_srev_type type, u_int16_t val);

int ath5k_init_ah(struct ath5k_hw *ah, const struct ath_bus_ops *bus_ops);
void ath5k_deinit_ah(struct ath5k_hw *ah);

/* Check whether BSSID mask is supported */
#define ath5k_hw_hasbssidmask(_ah) (ah->ah_version == AR5K_AR5212)

/* Check whether virtual EOL is supported */
#define ath5k_hw_hasveol(_ah) (ah->ah_version != AR5K_AR5210)

#endif	/* _DEV_ATH5K_BASE_H */
