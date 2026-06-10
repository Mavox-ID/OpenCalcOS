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
#ifndef ATH9K_HW_OPS_H
#define ATH9K_HW_OPS_H

#include "hw.h"

/* Hardware core and driver accessible callbacks */

static inline void ath9k_hw_configpcipowersave(struct ath_hw *ah,
					       bool power_off)
{
	if (!ah->aspm_enabled)
		return;

	ath9k_hw_ops(ah)->config_pci_powersave(ah, power_off);
}

static inline void ath9k_hw_rxena(struct ath_hw *ah)
{
	ath9k_hw_ops(ah)->rx_enable(ah);
}

static inline void ath9k_hw_set_desc_link(struct ath_hw *ah, void *ds,
					  u32 link)
{
	ath9k_hw_ops(ah)->set_desc_link(ds, link);
}

static inline bool ath9k_hw_calibrate(struct ath_hw *ah,
				      struct ath9k_channel *chan,
				      u8 rxchainmask,
				      bool longcal)
{
	return ath9k_hw_ops(ah)->calibrate(ah, chan, rxchainmask, longcal);
}

static inline bool ath9k_hw_getisr(struct ath_hw *ah, enum ath9k_int *masked)
{
	return ath9k_hw_ops(ah)->get_isr(ah, masked);
}

static inline void ath9k_hw_set_txdesc(struct ath_hw *ah, void *ds,
				       struct ath_tx_info *i)
{
	return ath9k_hw_ops(ah)->set_txdesc(ah, ds, i);
}

static inline int ath9k_hw_txprocdesc(struct ath_hw *ah, void *ds,
				      struct ath_tx_status *ts)
{
	return ath9k_hw_ops(ah)->proc_txdesc(ah, ds, ts);
}

static inline void ath9k_hw_antdiv_comb_conf_get(struct ath_hw *ah,
		struct ath_hw_antcomb_conf *antconf)
{
	ath9k_hw_ops(ah)->antdiv_comb_conf_get(ah, antconf);
}

static inline void ath9k_hw_antdiv_comb_conf_set(struct ath_hw *ah,
		struct ath_hw_antcomb_conf *antconf)
{
	ath9k_hw_ops(ah)->antdiv_comb_conf_set(ah, antconf);
}

static inline void ath9k_hw_antctrl_shared_chain_lnadiv(struct ath_hw *ah,
							bool enable)
{
	if (ath9k_hw_ops(ah)->antctrl_shared_chain_lnadiv)
		ath9k_hw_ops(ah)->antctrl_shared_chain_lnadiv(ah, enable);
}

/* Private hardware call ops */

/* PHY ops */

static inline int ath9k_hw_rf_set_freq(struct ath_hw *ah,
				       struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->rf_set_freq(ah, chan);
}

static inline void ath9k_hw_spur_mitigate_freq(struct ath_hw *ah,
					       struct ath9k_channel *chan)
{
	ath9k_hw_private_ops(ah)->spur_mitigate_freq(ah, chan);
}

static inline int ath9k_hw_rf_alloc_ext_banks(struct ath_hw *ah)
{
	if (!ath9k_hw_private_ops(ah)->rf_alloc_ext_banks)
		return 0;

	return ath9k_hw_private_ops(ah)->rf_alloc_ext_banks(ah);
}

static inline void ath9k_hw_rf_free_ext_banks(struct ath_hw *ah)
{
	if (!ath9k_hw_private_ops(ah)->rf_free_ext_banks)
		return;

	ath9k_hw_private_ops(ah)->rf_free_ext_banks(ah);
}

static inline bool ath9k_hw_set_rf_regs(struct ath_hw *ah,
					struct ath9k_channel *chan,
					u16 modesIndex)
{
	if (!ath9k_hw_private_ops(ah)->set_rf_regs)
		return true;

	return ath9k_hw_private_ops(ah)->set_rf_regs(ah, chan, modesIndex);
}

static inline void ath9k_hw_init_bb(struct ath_hw *ah,
				    struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->init_bb(ah, chan);
}

static inline void ath9k_hw_set_channel_regs(struct ath_hw *ah,
					     struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->set_channel_regs(ah, chan);
}

static inline int ath9k_hw_process_ini(struct ath_hw *ah,
					struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->process_ini(ah, chan);
}

static inline void ath9k_olc_init(struct ath_hw *ah)
{
	if (!ath9k_hw_private_ops(ah)->olc_init)
		return;

	return ath9k_hw_private_ops(ah)->olc_init(ah);
}

static inline void ath9k_hw_set_rfmode(struct ath_hw *ah,
				       struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->set_rfmode(ah, chan);
}

static inline void ath9k_hw_mark_phy_inactive(struct ath_hw *ah)
{
	return ath9k_hw_private_ops(ah)->mark_phy_inactive(ah);
}

static inline void ath9k_hw_set_delta_slope(struct ath_hw *ah,
					    struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->set_delta_slope(ah, chan);
}

static inline bool ath9k_hw_rfbus_req(struct ath_hw *ah)
{
	return ath9k_hw_private_ops(ah)->rfbus_req(ah);
}

static inline void ath9k_hw_rfbus_done(struct ath_hw *ah)
{
	return ath9k_hw_private_ops(ah)->rfbus_done(ah);
}

static inline void ath9k_hw_restore_chainmask(struct ath_hw *ah)
{
	if (!ath9k_hw_private_ops(ah)->restore_chainmask)
		return;

	return ath9k_hw_private_ops(ah)->restore_chainmask(ah);
}

static inline bool ath9k_hw_ani_control(struct ath_hw *ah,
					enum ath9k_ani_cmd cmd, int param)
{
	return ath9k_hw_private_ops(ah)->ani_control(ah, cmd, param);
}

static inline void ath9k_hw_do_getnf(struct ath_hw *ah,
				     int16_t nfarray[NUM_NF_READINGS])
{
	ath9k_hw_private_ops(ah)->do_getnf(ah, nfarray);
}

static inline bool ath9k_hw_init_cal(struct ath_hw *ah,
				     struct ath9k_channel *chan)
{
	return ath9k_hw_private_ops(ah)->init_cal(ah, chan);
}

static inline void ath9k_hw_setup_calibration(struct ath_hw *ah,
					      struct ath9k_cal_list *currCal)
{
	ath9k_hw_private_ops(ah)->setup_calibration(ah, currCal);
}

static inline int ath9k_hw_fast_chan_change(struct ath_hw *ah,
					    struct ath9k_channel *chan,
					    u8 *ini_reloaded)
{
	return ath9k_hw_private_ops(ah)->fast_chan_change(ah, chan,
							  ini_reloaded);
}

static inline void ath9k_hw_set_radar_params(struct ath_hw *ah)
{
	if (!ath9k_hw_private_ops(ah)->set_radar_params)
		return;

	ath9k_hw_private_ops(ah)->set_radar_params(ah, &ah->radar_conf);
}

#endif /* ATH9K_HW_OPS_H */
