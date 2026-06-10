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
#include "subdev/bios.h"
#include "subdev/bios/dcb.h"
#include "subdev/bios/i2c.h"

u16
dcb_i2c_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u16 i2c = 0x0000;
	u16 dcb = dcb_table(bios, ver, hdr, cnt, len);
	if (dcb) {
		if (*ver >= 0x15)
			i2c = nv_ro16(bios, dcb + 2);
		if (*ver >= 0x30)
			i2c = nv_ro16(bios, dcb + 4);
	}

	if (i2c && *ver >= 0x30) {
		*ver = nv_ro08(bios, i2c + 0);
		*hdr = nv_ro08(bios, i2c + 1);
		*cnt = nv_ro08(bios, i2c + 2);
		*len = nv_ro08(bios, i2c + 3);
	} else {
		*ver = *ver; /* use DCB version */
		*hdr = 0;
		*cnt = 16;
		*len = 4;
	}

	return i2c;
}

u16
dcb_i2c_entry(struct nouveau_bios *bios, u8 idx, u8 *ver, u8 *len)
{
	u8  hdr, cnt;
	u16 i2c = dcb_i2c_table(bios, ver, &hdr, &cnt, len);
	if (i2c && idx < cnt)
		return i2c + hdr + (idx * *len);
	return 0x0000;
}

int
dcb_i2c_parse(struct nouveau_bios *bios, u8 idx, struct dcb_i2c_entry *info)
{
	u8  ver, len;
	u16 ent = dcb_i2c_entry(bios, idx, &ver, &len);
	if (ent) {
		info->data = nv_ro32(bios, ent + 0);
		info->type = nv_ro08(bios, ent + 3);
		if (ver < 0x30) {
			info->type &= 0x07;
			if (info->type == 0x07)
				info->type = 0xff;
		}

		switch (info->type) {
		case DCB_I2C_NV04_BIT:
			info->drive = nv_ro08(bios, ent + 0);
			info->sense = nv_ro08(bios, ent + 1);
			return 0;
		case DCB_I2C_NV4E_BIT:
			info->drive = nv_ro08(bios, ent + 1);
			return 0;
		case DCB_I2C_NVIO_BIT:
		case DCB_I2C_NVIO_AUX:
			info->drive = nv_ro08(bios, ent + 0);
			return 0;
		case DCB_I2C_UNUSED:
			return 0;
		default:
			nv_warn(bios, "unknown i2c type %d\n", info->type);
			info->type = DCB_I2C_UNUSED;
			return 0;
		}
	}

	if (bios->bmp_offset && idx < 2) {
		/* BMP (from v4.0 has i2c info in the structure, it's in a
		 * fixed location on earlier VBIOS
		 */
		if (nv_ro08(bios, bios->bmp_offset + 5) < 4)
			ent = 0x0048;
		else
			ent = 0x0036 + bios->bmp_offset;

		if (idx == 0) {
			info->drive = nv_ro08(bios, ent + 4);
			if (!info->drive) info->drive = 0x3f;
			info->sense = nv_ro08(bios, ent + 5);
			if (!info->sense) info->sense = 0x3e;
		} else
		if (idx == 1) {
			info->drive = nv_ro08(bios, ent + 6);
			if (!info->drive) info->drive = 0x37;
			info->sense = nv_ro08(bios, ent + 7);
			if (!info->sense) info->sense = 0x36;
		}

		info->type = DCB_I2C_NV04_BIT;
		return 0;
	}

	return -ENOENT;
}
