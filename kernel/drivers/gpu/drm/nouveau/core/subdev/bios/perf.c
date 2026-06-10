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
#include <subdev/bios.h>
#include <subdev/bios/bit.h>
#include <subdev/bios/perf.h>

static u16
perf_table(struct nouveau_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	struct bit_entry bit_P;
	u16 perf = 0x0000;

	if (!bit_entry(bios, 'P', &bit_P)) {
		if (bit_P.version <= 2) {
			perf = nv_ro16(bios, bit_P.offset + 0);
			if (perf) {
				*ver = nv_ro08(bios, perf + 0);
				*hdr = nv_ro08(bios, perf + 1);
			}
		} else
			nv_error(bios, "unknown offset for perf in BIT P %d\n",
				bit_P.version);
	}

	if (bios->bmp_offset) {
		if (nv_ro08(bios, bios->bmp_offset + 6) >= 0x25) {
			perf = nv_ro16(bios, bios->bmp_offset + 0x94);
			if (perf) {
				*hdr = nv_ro08(bios, perf + 0);
				*ver = nv_ro08(bios, perf + 1);
			}
		}
	}

	return perf;
}

int
nvbios_perf_fan_parse(struct nouveau_bios *bios,
		      struct nvbios_perf_fan *fan)
{
	u8 ver = 0, hdr = 0, cnt = 0, len = 0;
	u16 perf = perf_table(bios, &ver, &hdr, &cnt, &len);
	if (!perf)
		return -ENODEV;

	if (ver >= 0x20 && ver < 0x40 && hdr > 6)
		fan->pwm_divisor = nv_ro16(bios, perf + 6);
	else
		fan->pwm_divisor = 0;

	return 0;
}
