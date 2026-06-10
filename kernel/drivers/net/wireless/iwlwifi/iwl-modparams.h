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
#ifndef __iwl_modparams_h__
#define __iwl_modparams_h__

#include <beep/types.h>
#include <beep/spinlock.h>
#include <beep/gfp.h>
#include <net/mac80211.h>

extern struct iwl_mod_params iwlwifi_mod_params;

enum iwl_power_level {
	IWL_POWER_INDEX_1,
	IWL_POWER_INDEX_2,
	IWL_POWER_INDEX_3,
	IWL_POWER_INDEX_4,
	IWL_POWER_INDEX_5,
	IWL_POWER_NUM
};

#define IWL_DISABLE_HT_ALL	BIT(0)
#define IWL_DISABLE_HT_TXAGG	BIT(1)
#define IWL_DISABLE_HT_RXAGG	BIT(2)

/**
 * struct iwl_mod_params
 *
 * Holds the module parameters
 *
 * @sw_crypto: using hardware encryption, default = 0
 * @disable_11n: disable 11n capabilities, default = 0,
 *	use IWL_DISABLE_HT_* constants
 * @amsdu_size_8K: enable 8K amsdu size, default = 1
 * @restart_fw: restart firmware, default = 1
 * @plcp_check: enable plcp health check, default = true
 * @wd_disable: enable stuck queue check, default = 0
 * @bt_coex_active: enable bt coex, default = true
 * @led_mode: system default, default = 0
 * @power_save: disable power save, default = false
 * @power_level: power level, default = 1
 * @debug_level: levels are IWL_DL_*
 * @ant_coupling: antenna coupling in dB, default = 0
 * @bt_ch_announce: BT channel inhibition, default = enable
 * @auto_agg: enable agg. without check, default = true
 * @disable_5ghz: disable 5GHz capability, default = false
 */
struct iwl_mod_params {
	int sw_crypto;
	unsigned int disable_11n;
	int amsdu_size_8K;
	int restart_fw;
	bool plcp_check;
	int  wd_disable;
	bool bt_coex_active;
	int led_mode;
	bool power_save;
	int power_level;
	u32 debug_level;
	int ant_coupling;
	bool bt_ch_announce;
	bool auto_agg;
	bool disable_5ghz;
};

#endif /* #__iwl_modparams_h__ */
