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
#ifndef __ASM_ARCH_CAMERA_H_
#define __ASM_ARCH_CAMERA_H_

#define MX1_CAMERA_DATA_HIGH	1
#define MX1_CAMERA_PCLK_RISING	2
#define MX1_CAMERA_VSYNC_HIGH	4

extern unsigned char mx1_camera_sof_fiq_start, mx1_camera_sof_fiq_end;

/**
 * struct mx1_camera_pdata - i.MX1/i.MXL camera platform data
 * @mclk_10khz:	master clock frequency in 10kHz units
 * @flags:	MX1 camera platform flags
 */
struct mx1_camera_pdata {
	unsigned long mclk_10khz;
	unsigned long flags;
};

#endif /* __ASM_ARCH_CAMERA_H_ */
