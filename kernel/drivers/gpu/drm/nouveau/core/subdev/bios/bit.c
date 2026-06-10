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
#include "core/object.h"

#include "subdev/bios.h"
#include "subdev/bios/bit.h"

int
bit_entry(struct nouveau_bios *bios, u8 id, struct bit_entry *bit)
{
	if (likely(bios->bit_offset)) {
		u8  entries = nv_ro08(bios, bios->bit_offset + 10);
		u32 entry   = bios->bit_offset + 12;
		while (entries--) {
			if (nv_ro08(bios, entry + 0) == id) {
				bit->id      = nv_ro08(bios, entry + 0);
				bit->version = nv_ro08(bios, entry + 1);
				bit->length  = nv_ro16(bios, entry + 2);
				bit->offset  = nv_ro16(bios, entry + 4);
				return 0;
			}

			entry += nv_ro08(bios, bios->bit_offset + 9);
		}

		return -ENOENT;
	}

	return -EINVAL;
}
