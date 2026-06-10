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
#ifndef __BEEP_PLATFORM_DATA_AD5449_H__
#define __BEEP_PLATFORM_DATA_AD5449_H__

/**
 * enum ad5449_sdo_mode - AD5449 SDO pin configuration
 * @AD5449_SDO_DRIVE_FULL: Drive the SDO pin with full strength.
 * @AD5449_SDO_DRIVE_WEAK: Drive the SDO pin with not full strength.
 * @AD5449_SDO_OPEN_DRAIN: Operate the SDO pin in open-drain mode.
 * @AD5449_SDO_DISABLED: Disable the SDO pin, in this mode it is not possible to
 *			read back from the device.
 */
enum ad5449_sdo_mode {
	AD5449_SDO_DRIVE_FULL = 0x0,
	AD5449_SDO_DRIVE_WEAK = 0x1,
	AD5449_SDO_OPEN_DRAIN = 0x2,
	AD5449_SDO_DISABLED = 0x3,
};

/**
 * struct ad5449_platform_data - Platform data for the ad5449 DAC driver
 * @sdo_mode: SDO pin mode
 * @hardware_clear_to_midscale: Whether asserting the hardware CLR pin sets the
 *			outputs to midscale (true) or to zero scale(false).
 */
struct ad5449_platform_data {
	enum ad5449_sdo_mode sdo_mode;
	bool hardware_clear_to_midscale;
};

#endif
