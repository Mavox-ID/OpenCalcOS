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
#ifndef __WL12XX_CMD_H__
#define __WL12XX_CMD_H__

#include "conf.h"

#define TEST_CMD_INI_FILE_RADIO_PARAM       0x19
#define TEST_CMD_INI_FILE_GENERAL_PARAM     0x1E

struct wl1271_general_parms_cmd {
	struct wl1271_cmd_header header;

	struct wl1271_cmd_test_header test;

	struct wl1271_ini_general_params general_params;

	u8 sr_debug_table[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 sr_sen_n_p;
	u8 sr_sen_n_p_gain;
	u8 sr_sen_nrn;
	u8 sr_sen_prn;
	u8 padding[3];
} __packed;

struct wl128x_general_parms_cmd {
	struct wl1271_cmd_header header;

	struct wl1271_cmd_test_header test;

	struct wl128x_ini_general_params general_params;

	u8 sr_debug_table[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 sr_sen_n_p;
	u8 sr_sen_n_p_gain;
	u8 sr_sen_nrn;
	u8 sr_sen_prn;
	u8 padding[3];
} __packed;

struct wl1271_radio_parms_cmd {
	struct wl1271_cmd_header header;

	struct wl1271_cmd_test_header test;

	/* Static radio parameters */
	struct wl1271_ini_band_params_2 static_params_2;
	struct wl1271_ini_band_params_5 static_params_5;

	/* Dynamic radio parameters */
	struct wl1271_ini_fem_params_2 dyn_params_2;
	u8 padding2;
	struct wl1271_ini_fem_params_5 dyn_params_5;
	u8 padding3[2];
} __packed;

struct wl128x_radio_parms_cmd {
	struct wl1271_cmd_header header;

	struct wl1271_cmd_test_header test;

	/* Static radio parameters */
	struct wl128x_ini_band_params_2 static_params_2;
	struct wl128x_ini_band_params_5 static_params_5;

	u8 fem_vendor_and_options;

	/* Dynamic radio parameters */
	struct wl128x_ini_fem_params_2 dyn_params_2;
	u8 padding2;
	struct wl128x_ini_fem_params_5 dyn_params_5;
} __packed;

#define TEST_CMD_INI_FILE_RF_EXTENDED_PARAM 0x26

struct wl1271_ext_radio_parms_cmd {
	struct wl1271_cmd_header header;

	struct wl1271_cmd_test_header test;

	u8 tx_per_channel_power_compensation_2[CONF_TX_PWR_COMPENSATION_LEN_2];
	u8 tx_per_channel_power_compensation_5[CONF_TX_PWR_COMPENSATION_LEN_5];
	u8 padding[3];
} __packed;

int wl1271_cmd_general_parms(struct wl1271 *wl);
int wl128x_cmd_general_parms(struct wl1271 *wl);
int wl1271_cmd_radio_parms(struct wl1271 *wl);
int wl128x_cmd_radio_parms(struct wl1271 *wl);
int wl1271_cmd_ext_radio_parms(struct wl1271 *wl);

#endif /* __WL12XX_CMD_H__ */
