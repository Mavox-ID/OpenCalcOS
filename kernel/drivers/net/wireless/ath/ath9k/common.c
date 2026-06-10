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
 * Module for common driver code between ath9k and ath9k_htc
 */

#include <beep/kernel.h>
#include <beep/module.h>

#include "common.h"

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Shared library for Atheros wireless 802.11n LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

int ath9k_cmn_padpos(__le16 frame_control)
{
	int padpos = 24;
	if (ieee80211_has_a4(frame_control)) {
		padpos += ETH_ALEN;
	}
	if (ieee80211_is_data_qos(frame_control)) {
		padpos += IEEE80211_QOS_CTL_LEN;
	}

	return padpos;
}
EXPORT_SYMBOL(ath9k_cmn_padpos);

int ath9k_cmn_get_hw_crypto_keytype(struct sk_buff *skb)
{
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	if (tx_info->control.hw_key) {
		switch (tx_info->control.hw_key->cipher) {
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			return ATH9K_KEY_TYPE_WEP;
		case WLAN_CIPHER_SUITE_TKIP:
			return ATH9K_KEY_TYPE_TKIP;
		case WLAN_CIPHER_SUITE_CCMP:
			return ATH9K_KEY_TYPE_AES;
		default:
			break;
		}
	}

	return ATH9K_KEY_TYPE_CLEAR;
}
EXPORT_SYMBOL(ath9k_cmn_get_hw_crypto_keytype);

static u32 ath9k_get_extchanmode(struct ieee80211_channel *chan,
				 enum nl80211_channel_type channel_type)
{
	u32 chanmode = 0;

	switch (chan->band) {
	case IEEE80211_BAND_2GHZ:
		switch (channel_type) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
			chanmode = CHANNEL_G_HT20;
			break;
		case NL80211_CHAN_HT40PLUS:
			chanmode = CHANNEL_G_HT40PLUS;
			break;
		case NL80211_CHAN_HT40MINUS:
			chanmode = CHANNEL_G_HT40MINUS;
			break;
		}
		break;
	case IEEE80211_BAND_5GHZ:
		switch (channel_type) {
		case NL80211_CHAN_NO_HT:
		case NL80211_CHAN_HT20:
			chanmode = CHANNEL_A_HT20;
			break;
		case NL80211_CHAN_HT40PLUS:
			chanmode = CHANNEL_A_HT40PLUS;
			break;
		case NL80211_CHAN_HT40MINUS:
			chanmode = CHANNEL_A_HT40MINUS;
			break;
		}
		break;
	default:
		break;
	}

	return chanmode;
}

/*
 * Update internal channel flags.
 */
void ath9k_cmn_update_ichannel(struct ath9k_channel *ichan,
			       struct ieee80211_channel *chan,
			       enum nl80211_channel_type channel_type)
{
	ichan->channel = chan->center_freq;
	ichan->chan = chan;

	if (chan->band == IEEE80211_BAND_2GHZ) {
		ichan->chanmode = CHANNEL_G;
		ichan->channelFlags = CHANNEL_2GHZ | CHANNEL_OFDM;
	} else {
		ichan->chanmode = CHANNEL_A;
		ichan->channelFlags = CHANNEL_5GHZ | CHANNEL_OFDM;
	}

	if (channel_type != NL80211_CHAN_NO_HT)
		ichan->chanmode = ath9k_get_extchanmode(chan, channel_type);
}
EXPORT_SYMBOL(ath9k_cmn_update_ichannel);

/*
 * Get the internal channel reference.
 */
struct ath9k_channel *ath9k_cmn_get_curchannel(struct ieee80211_hw *hw,
					       struct ath_hw *ah)
{
	struct ieee80211_channel *curchan = hw->conf.channel;
	struct ath9k_channel *channel;
	u8 chan_idx;

	chan_idx = curchan->hw_value;
	channel = &ah->channels[chan_idx];
	ath9k_cmn_update_ichannel(channel, curchan, hw->conf.channel_type);

	return channel;
}
EXPORT_SYMBOL(ath9k_cmn_get_curchannel);

int ath9k_cmn_count_streams(unsigned int chainmask, int max)
{
	int streams = 0;

	do {
		if (++streams == max)
			break;
	} while ((chainmask = chainmask & (chainmask - 1)));

	return streams;
}
EXPORT_SYMBOL(ath9k_cmn_count_streams);

void ath9k_cmn_update_txpow(struct ath_hw *ah, u16 cur_txpow,
			    u16 new_txpow, u16 *txpower)
{
	struct ath_regulatory *reg = ath9k_hw_regulatory(ah);

	if (reg->power_limit != new_txpow) {
		ath9k_hw_set_txpowerlimit(ah, new_txpow, false);
		/* read back in case value is clamped */
		*txpower = reg->max_power_level;
	}
}
EXPORT_SYMBOL(ath9k_cmn_update_txpow);

void ath9k_cmn_init_crypto(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int i = 0;

	/* Get the hardware key cache size. */
	common->keymax = AR_KEYTABLE_SIZE;

	/*
	 * Check whether the separate key cache entries
	 * are required to handle both tx+rx MIC keys.
	 * With split mic keys the number of stations is limited
	 * to 27 otherwise 59.
	 */
	if (ah->misc_mode & AR_PCU_MIC_NEW_LOC_ENA)
		common->crypt_caps |= ATH_CRYPT_CAP_MIC_COMBINED;

	/*
	 * Reset the key cache since some parts do not
	 * reset the contents on initial power up.
	 */
	for (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);
}
EXPORT_SYMBOL(ath9k_cmn_init_crypto);

static int __init ath9k_cmn_init(void)
{
	return 0;
}
module_init(ath9k_cmn_init);

static void __exit ath9k_cmn_exit(void)
{
	return;
}
module_exit(ath9k_cmn_exit);
