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
nva3_hda_eld(struct nv50_disp_priv *priv, int or, u8 *data, u32 size)
{
	const u32 soff = (or * 0x800);
	int i;

	if (data && data[0]) {
		for (i = 0; i < size; i++)
			nv_wr32(priv, 0x61c440 + soff, (i << 8) | data[i]);
		nv_mask(priv, 0x61c448 + soff, 0x80000003, 0x80000003);
	} else
	if (data) {
		nv_mask(priv, 0x61c448 + soff, 0x80000003, 0x80000001);
	} else {
		nv_mask(priv, 0x61c448 + soff, 0x80000003, 0x80000000);
	}

	return 0;
}
