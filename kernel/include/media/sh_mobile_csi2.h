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
#ifndef SH_MIPI_CSI
#define SH_MIPI_CSI

#include <beep/list.h>

enum sh_csi2_phy {
	SH_CSI2_PHY_MAIN,
	SH_CSI2_PHY_SUB,
};

enum sh_csi2_type {
	SH_CSI2C,
	SH_CSI2I,
};

#define SH_CSI2_CRC	(1 << 0)
#define SH_CSI2_ECC	(1 << 1)

struct platform_device;

struct sh_csi2_client_config {
	enum sh_csi2_phy phy;
	unsigned char lanes;		/* bitmask[3:0] */
	unsigned char channel;		/* 0..3 */
	struct platform_device *pdev;	/* client platform device */
};

struct v4l2_device;

struct sh_csi2_pdata {
	enum sh_csi2_type type;
	unsigned int flags;
	struct sh_csi2_client_config *clients;
	int num_clients;
	struct v4l2_device *v4l2_dev;
};

#endif
