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
nva3_hdmi_ctrl(struct nv50_disp_priv *priv, int head, int or, u32 data)
{
	const u32 soff = (or * 0x800);

	if (!(data & NV84_DISP_SOR_HDMI_PWR_STATE_ON)) {
		nv_mask(priv, 0x61c5a4 + soff, 0x40000000, 0x00000000);
		nv_mask(priv, 0x61c520 + soff, 0x00000001, 0x00000000);
		nv_mask(priv, 0x61c500 + soff, 0x00000001, 0x00000000);
		return 0;
	}

	/* AVI InfoFrame */
	nv_mask(priv, 0x61c520 + soff, 0x00000001, 0x00000000);
	nv_wr32(priv, 0x61c528 + soff, 0x000d0282);
	nv_wr32(priv, 0x61c52c + soff, 0x0000006f);
	nv_wr32(priv, 0x61c530 + soff, 0x00000000);
	nv_wr32(priv, 0x61c534 + soff, 0x00000000);
	nv_wr32(priv, 0x61c538 + soff, 0x00000000);
	nv_mask(priv, 0x61c520 + soff, 0x00000001, 0x00000001);

	/* Audio InfoFrame */
	nv_mask(priv, 0x61c500 + soff, 0x00000001, 0x00000000);
	nv_wr32(priv, 0x61c508 + soff, 0x000a0184);
	nv_wr32(priv, 0x61c50c + soff, 0x00000071);
	nv_wr32(priv, 0x61c510 + soff, 0x00000000);
	nv_mask(priv, 0x61c500 + soff, 0x00000001, 0x00000001);

	/* ??? */
	nv_mask(priv, 0x61733c, 0x00100000, 0x00100000); /* RESETF */
	nv_mask(priv, 0x61733c, 0x10000000, 0x10000000); /* LOOKUP_EN */
	nv_mask(priv, 0x61733c, 0x00100000, 0x00000000); /* !RESETF */

	/* HDMI_CTRL */
	nv_mask(priv, 0x61c5a4 + soff, 0x5f1f007f, data | 0x1f000000 /* ??? */);
	return 0;
}
