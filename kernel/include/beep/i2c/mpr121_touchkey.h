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
#ifndef _MPR121_TOUCHKEY_H
#define _MPR121_TOUCHKEY_H

/**
 * struct mpr121_platform_data - platform data for mpr121 sensor
 * @keymap: pointer to array of KEY_* values representing keymap
 * @keymap_size: size of the keymap
 * @wakeup: configure the button as a wake-up source
 * @vdd_uv: VDD voltage in uV
 */
struct mpr121_platform_data {
	const unsigned short *keymap;
	unsigned int keymap_size;
	bool wakeup;
	int vdd_uv;
};

#endif /* _MPR121_TOUCHKEY_H */
