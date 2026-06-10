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
#ifndef _MAX9877_H
#define _MAX9877_H

#define MAX9877_INPUT_MODE		0x00
#define MAX9877_SPK_VOLUME		0x01
#define MAX9877_HPL_VOLUME		0x02
#define MAX9877_HPR_VOLUME		0x03
#define MAX9877_OUTPUT_MODE		0x04

/* MAX9877_INPUT_MODE */
#define MAX9877_INB			(1 << 4)
#define MAX9877_INA			(1 << 5)
#define MAX9877_ZCD			(1 << 6)

/* MAX9877_OUTPUT_MODE */
#define MAX9877_OUTMODE_MASK		(15 << 0)
#define MAX9877_OSC_MASK		(3 << 4)
#define MAX9877_OSC_OFFSET		4
#define MAX9877_BYPASS			(1 << 6)
#define MAX9877_SHDN			(1 << 7)

extern int max9877_add_controls(struct snd_soc_codec *codec);

#endif
