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
#include <core/device.h>

#include <subdev/bios.h>
#include <subdev/bios/dcb.h>
#include <subdev/bios/conn.h>

u16
dcb_conntab(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb && *ver >= 0x30 && *hdr >= 0x16) {
		u16 data = nv_ro16(bios, dcb + 0x14);
		if (data) {
			*ver = nv_ro08(bios, data + 0);
			*hdr = nv_ro08(bios, data + 1);
			*cnt = nv_ro08(bios, data + 2);
			*len = nv_ro08(bios, data + 3);
			return data;
		}
	}
	return 0x0000;
}

u16
dcb_conn(struct nouveau_bios *bios, u8 idx, u8 *ver, u8 *len)
{
	u8  hdr, cnt;
	u16 data = dcb_conntab(bios, ver, &hdr, &cnt, len);
	if (data && idx < cnt)
		return data + hdr + (idx * *len);
	return 0x0000;
}
