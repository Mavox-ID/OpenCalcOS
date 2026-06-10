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
#include "check.h"
#include "karma.h"

int karma_partition(struct parsed_partitions *state)
{
	int i;
	int slot = 1;
	Sector sect;
	unsigned char *data;
	struct disklabel {
		u8 d_reserved[270];
		struct d_partition {
			__le32 p_res;
			u8 p_fstype;
			u8 p_res2[3];
			__le32 p_offset;
			__le32 p_size;
		} d_partitions[2];
		u8 d_blank[208];
		__le16 d_magic;
	} __attribute__((packed)) *label;
	struct d_partition *p;

	data = read_part_sector(state, 0, &sect);
	if (!data)
		return -1;

	label = (struct disklabel *)data;
	if (le16_to_cpu(label->d_magic) != KARMA_LABEL_MAGIC) {
		put_dev_sector(sect);
		return 0;
	}

	p = label->d_partitions;
	for (i = 0 ; i < 2; i++, p++) {
		if (slot == state->limit)
			break;

		if (p->p_fstype == 0x4d && le32_to_cpu(p->p_size)) {
			put_partition(state, slot, le32_to_cpu(p->p_offset),
				le32_to_cpu(p->p_size));
		}
		slot++;
	}
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	return 1;
}

