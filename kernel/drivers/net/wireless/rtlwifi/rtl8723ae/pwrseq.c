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
#include "pwrseqcmd.h"
#include "pwrseq.h"

/* drivers should parse arrays below and do the corresponding actions */

/*3 Power on  Array*/
struct wlan_pwr_cfg rtl8723A_power_on_flow[RTL8723A_TRANS_CARDEMU_TO_ACT_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_CARDEMU_TO_ACT,
	RTL8723A_TRANS_END
};

/*3Radio off GPIO Array */
struct wlan_pwr_cfg rtl8723A_radio_off_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_ACT_TO_CARDEMU,
	RTL8723A_TRANS_END
};

/*3Card Disable Array*/
struct wlan_pwr_cfg
rtl8723A_card_disable_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
			  + RTL8723A_TRANS_CARDEMU_TO_PDN_STPS
			  + RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_ACT_TO_CARDEMU,
	RTL8723A_TRANS_CARDEMU_TO_CARDDIS,
	RTL8723A_TRANS_END
};

/*3 Card Enable Array*/
struct wlan_pwr_cfg rtl8723A_card_enable_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
					+ RTL8723A_TRANS_CARDEMU_TO_PDN_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_CARDDIS_TO_CARDEMU,
	RTL8723A_TRANS_CARDEMU_TO_ACT,
	RTL8723A_TRANS_END
};

/*3Suspend Array*/
struct wlan_pwr_cfg rtl8723A_suspend_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
					+ RTL8723A_TRANS_CARDEMU_TO_SUS_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_ACT_TO_CARDEMU,
	RTL8723A_TRANS_CARDEMU_TO_SUS,
	RTL8723A_TRANS_END
};

/*3 Resume Array*/
struct wlan_pwr_cfg rtl8723A_resume_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
					+ RTL8723A_TRANS_CARDEMU_TO_SUS_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_SUS_TO_CARDEMU,
	RTL8723A_TRANS_CARDEMU_TO_ACT,
	RTL8723A_TRANS_END
};

/*3HWPDN Array*/
struct wlan_pwr_cfg rtl8723A_hwpdn_flow[RTL8723A_TRANS_ACT_TO_CARDEMU_STPS
				+ RTL8723A_TRANS_CARDEMU_TO_PDN_STPS
				+ RTL8723A_TRANS_END_STPS] = {
	RTL8723A_TRANS_ACT_TO_CARDEMU,
	RTL8723A_TRANS_CARDEMU_TO_PDN,
	RTL8723A_TRANS_END
};

/*3 Enter LPS */
struct wlan_pwr_cfg rtl8723A_enter_lps_flow[RTL8723A_TRANS_ACT_TO_LPS_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	/*FW behavior*/
	RTL8723A_TRANS_ACT_TO_LPS,
	RTL8723A_TRANS_END
};

/*3 Leave LPS */
struct wlan_pwr_cfg rtl8723A_leave_lps_flow[RTL8723A_TRANS_LPS_TO_ACT_STPS
					+ RTL8723A_TRANS_END_STPS] = {
	/*FW behavior*/
	RTL8723A_TRANS_LPS_TO_ACT,
	RTL8723A_TRANS_END
};
