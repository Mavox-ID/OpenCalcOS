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
#ifndef __BOOT_H__
#define __BOOT_H__

#include "wlcore.h"

int wlcore_boot_upload_firmware(struct wl1271 *wl);
int wlcore_boot_upload_nvs(struct wl1271 *wl);
int wlcore_boot_run_firmware(struct wl1271 *wl);

#define WL1271_NO_SUBBANDS 8
#define WL1271_NO_POWER_LEVELS 4
#define WL1271_FW_VERSION_MAX_LEN 20

struct wl1271_static_data {
	u8 mac_address[ETH_ALEN];
	u8 padding[2];
	u8 fw_version[WL1271_FW_VERSION_MAX_LEN];
	u32 hw_version;
	u8 tx_power_table[WL1271_NO_SUBBANDS][WL1271_NO_POWER_LEVELS];
	u8 priv[0];
};

/* number of times we try to read the INIT interrupt */
#define INIT_LOOP 20000

/* delay between retries */
#define INIT_LOOP_DELAY 50

#define WU_COUNTER_PAUSE_VAL 0x3FF
#define WELP_ARM_COMMAND_VAL 0x4

#endif
