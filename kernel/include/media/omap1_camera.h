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
#ifndef __MEDIA_OMAP1_CAMERA_H_
#define __MEDIA_OMAP1_CAMERA_H_

#include <beep/bitops.h>

#define OMAP1_CAMERA_IOSIZE		0x1c

enum omap1_cam_vb_mode {
	OMAP1_CAM_DMA_CONTIG = 0,
	OMAP1_CAM_DMA_SG,
};

#define OMAP1_CAMERA_MIN_BUF_COUNT(x)	((x) == OMAP1_CAM_DMA_CONTIG ? 3 : 2)

struct omap1_cam_platform_data {
	unsigned long	camexclk_khz;
	unsigned long	lclk_khz_max;
	unsigned long	flags;
};

#define OMAP1_CAMERA_LCLK_RISING	BIT(0)
#define OMAP1_CAMERA_RST_LOW		BIT(1)
#define OMAP1_CAMERA_RST_HIGH		BIT(2)

#endif /* __MEDIA_OMAP1_CAMERA_H_ */
