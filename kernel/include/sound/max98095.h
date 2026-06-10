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
#ifndef __SOUND_MAX98095_PDATA_H__
#define __SOUND_MAX98095_PDATA_H__

/* Equalizer filter response configuration */
struct max98095_eq_cfg {
	const char *name;
	unsigned int rate;
	u16 band1[5];
	u16 band2[5];
	u16 band3[5];
	u16 band4[5];
	u16 band5[5];
};

/* Biquad filter response configuration */
struct max98095_biquad_cfg {
	const char *name;
	unsigned int rate;
	u16 band1[5];
	u16 band2[5];
};

/* codec platform data */
struct max98095_pdata {

	/* Equalizers for DAI1 and DAI2 */
	struct max98095_eq_cfg *eq_cfg;
	unsigned int eq_cfgcnt;

	/* Biquad filter for DAI1 and DAI2 */
	struct max98095_biquad_cfg *bq_cfg;
	unsigned int bq_cfgcnt;

	/* Analog/digital microphone configuration:
	 * 0 = analog microphone input (normal setting)
	 * 1 = digital microphone input
	 */
	unsigned int digmic_left_mode:1;
	unsigned int digmic_right_mode:1;

	/* Pin5 is the mechanical method of sensing jack insertion
	 * but it is something that might not be supported.
	 * 0 = PIN5 not supported
	 * 1 = PIN5 supported
	 */
	unsigned int jack_detect_pin5en:1;

	/* Slew amount for jack detection. Calculated as 4 * (delay + 1).
	 * Default delay is 24 to get a time of 100ms.
	 */
	unsigned int jack_detect_delay;
};

#endif
