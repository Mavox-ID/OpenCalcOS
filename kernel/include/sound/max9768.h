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
#ifndef __SOUND_MAX9768_PDATA_H__
#define __SOUND_MAX9768_PDATA_H__

/**
 * struct max9768_pdata - optional platform specific MAX9768 configuration
 * @shdn_gpio:	GPIO to SHDN pin. If not valid, pin must be hardwired HIGH
 * @mute_gpio:	GPIO to MUTE pin. If not valid, control for mute won't be added
 * @flags: configuration flags, e.g. set classic PWM mode (check datasheet
 *         regarding "filterless modulation" which is default).
 */
struct max9768_pdata {
	int shdn_gpio;
	int mute_gpio;
	unsigned flags;
#define MAX9768_FLAG_CLASSIC_PWM	(1 << 0)
};

#endif /* __SOUND_MAX9768_PDATA_H__*/
