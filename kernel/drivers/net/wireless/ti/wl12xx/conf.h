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
#ifndef __WL12XX_CONF_H__
#define __WL12XX_CONF_H__

/* these are number of channels on the band divided by two, rounded up */
#define CONF_TX_PWR_COMPENSATION_LEN_2 7
#define CONF_TX_PWR_COMPENSATION_LEN_5 18

struct wl12xx_conf_rf {
	/*
	 * Per channel power compensation for 2.4GHz
	 *
	 * Range: s8
	 */
	u8 tx_per_channel_power_compensation_2[CONF_TX_PWR_COMPENSATION_LEN_2];

	/*
	 * Per channel power compensation for 5GHz
	 *
	 * Range: s8
	 */
	u8 tx_per_channel_power_compensation_5[CONF_TX_PWR_COMPENSATION_LEN_5];
};

struct wl12xx_priv_conf {
	struct wl12xx_conf_rf rf;
	struct conf_memory_settings mem_wl127x;
};

#endif /* __WL12XX_CONF_H__ */
