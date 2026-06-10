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
#ifndef __MACH_MX2_CAM_H_
#define __MACH_MX2_CAM_H_

#define MX2_CAMERA_EXT_VSYNC		(1 << 1)
#define MX2_CAMERA_CCIR			(1 << 2)
#define MX2_CAMERA_CCIR_INTERLACE	(1 << 3)
#define MX2_CAMERA_HSYNC_HIGH		(1 << 4)
#define MX2_CAMERA_GATED_CLOCK		(1 << 5)
#define MX2_CAMERA_INV_DATA		(1 << 6)
#define MX2_CAMERA_PCLK_SAMPLE_RISING	(1 << 7)

/**
 * struct mx2_camera_platform_data - optional platform data for mx2_camera
 * @flags: any combination of MX2_CAMERA_*
 * @clk: clock rate of the csi block / 2
 */
struct mx2_camera_platform_data {
	unsigned long flags;
	unsigned long clk;
};

#endif /* __MACH_MX2_CAM_H_ */
