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
#include <core/os.h>
#include <core/class.h>

#include "nv50.h"

int
nvd0_hdmi_ctrl(struct nv50_disp_priv *priv, int head, int or, u32 data)
{
	const u32 hoff = (head * 0x800);

	if (!(data & NV84_DISP_SOR_HDMI_PWR_STATE_ON)) {
		nv_mask(priv, 0x616798 + hoff, 0x40000000, 0x00000000);
		nv_mask(priv, 0x6167a4 + hoff, 0x00000001, 0x00000000);
		nv_mask(priv, 0x616714 + hoff, 0x00000001, 0x00000000);
		return 0;
	}

	/* AVI InfoFrame */
	nv_mask(priv, 0x616714 + hoff, 0x00000001, 0x00000000);
	nv_wr32(priv, 0x61671c + hoff, 0x000d0282);
	nv_wr32(priv, 0x616720 + hoff, 0x0000006f);
	nv_wr32(priv, 0x616724 + hoff, 0x00000000);
	nv_wr32(priv, 0x616728 + hoff, 0x00000000);
	nv_wr32(priv, 0x61672c + hoff, 0x00000000);
	nv_mask(priv, 0x616714 + hoff, 0x00000001, 0x00000001);

	/* ??? InfoFrame? */
	nv_mask(priv, 0x6167a4 + hoff, 0x00000001, 0x00000000);
	nv_wr32(priv, 0x6167ac + hoff, 0x00000010);
	nv_mask(priv, 0x6167a4 + hoff, 0x00000001, 0x00000001);

	/* HDMI_CTRL */
	nv_mask(priv, 0x616798 + hoff, 0x401f007f, data);

	/* NFI, audio doesn't work without it though.. */
	nv_mask(priv, 0x616548 + hoff, 0x00000070, 0x00000000);
	return 0;
}
