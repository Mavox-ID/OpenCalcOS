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
#ifndef __CS42L52_H
#define __CS42L52_H

struct cs42l52_platform_data {

	/* MICBIAS Level. Check datasheet Pg48 */
	unsigned int micbias_lvl;

	/* MICA mode selection 0=Single 1=Differential */
	unsigned int mica_cfg;

	/* MICB mode selection 0=Single 1=Differential */
	unsigned int micb_cfg;

	/* MICA Select 0=MIC1A 1=MIC2A */
	unsigned int mica_sel;

	/* MICB Select 0=MIC2A 1=MIC2B */
	unsigned int micb_sel;

	/* Charge Pump Freq. Check datasheet Pg73 */
	unsigned int chgfreq;

};

#endif /* __CS42L52_H */
