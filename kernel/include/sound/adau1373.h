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
#ifndef __SOUND_ADAU1373_H__
#define __SOUND_ADAU1373_H__

enum adau1373_micbias_voltage {
	ADAU1373_MICBIAS_2_9V = 0,
	ADAU1373_MICBIAS_2_2V = 1,
	ADAU1373_MICBIAS_2_6V = 2,
	ADAU1373_MICBIAS_1_8V = 3,
};

#define ADAU1373_DRC_SIZE 13

struct adau1373_platform_data {
	bool input_differential[4];
	bool lineout_differential;
	bool lineout_ground_sense;

	unsigned int num_drc;
	uint8_t drc_setting[3][ADAU1373_DRC_SIZE];

	enum adau1373_micbias_voltage micbias1;
	enum adau1373_micbias_voltage micbias2;
};

#endif
