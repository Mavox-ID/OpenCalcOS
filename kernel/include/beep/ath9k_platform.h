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
#ifndef _BEEP_ATH9K_PLATFORM_H
#define _BEEP_ATH9K_PLATFORM_H

#define ATH9K_PLAT_EEP_MAX_WORDS	2048

struct ath9k_platform_data {
	const char *eeprom_name;

	u16 eeprom_data[ATH9K_PLAT_EEP_MAX_WORDS];
	u8 *macaddr;

	int led_pin;
	u32 gpio_mask;
	u32 gpio_val;

	bool is_clk_25mhz;
	int (*get_mac_revision)(void);
	int (*external_reset)(void);
};

#endif /* _BEEP_ATH9K_PLATFORM_H */
