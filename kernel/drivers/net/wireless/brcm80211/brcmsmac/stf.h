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
#ifndef _BRCM_STF_H_
#define _BRCM_STF_H_

#include "types.h"

extern int brcms_c_stf_attach(struct brcms_c_info *wlc);
extern void brcms_c_stf_detach(struct brcms_c_info *wlc);

extern void brcms_c_tempsense_upd(struct brcms_c_info *wlc);
extern void brcms_c_stf_ss_algo_channel_get(struct brcms_c_info *wlc,
					u16 *ss_algo_channel,
					u16 chanspec);
extern int brcms_c_stf_ss_update(struct brcms_c_info *wlc,
			     struct brcms_band *band);
extern void brcms_c_stf_phy_txant_upd(struct brcms_c_info *wlc);
extern int brcms_c_stf_txchain_set(struct brcms_c_info *wlc, s32 int_val,
			       bool force);
extern bool brcms_c_stf_stbc_rx_set(struct brcms_c_info *wlc, s32 int_val);
extern void brcms_c_stf_phy_txant_upd(struct brcms_c_info *wlc);
extern void brcms_c_stf_phy_chain_calc(struct brcms_c_info *wlc);
extern u16 brcms_c_stf_phytxchain_sel(struct brcms_c_info *wlc,
				      u32 rspec);
extern u16 brcms_c_stf_d11hdrs_phyctl_txant(struct brcms_c_info *wlc,
					u32 rspec);

#endif				/* _BRCM_STF_H_ */
