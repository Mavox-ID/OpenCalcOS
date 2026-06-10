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
#include "ultrix.h"

int ultrix_partition(struct parsed_partitions *state)
{
	int i;
	Sector sect;
	unsigned char *data;
	struct ultrix_disklabel {
		s32	pt_magic;	/* magic no. indicating part. info exits */
		s32	pt_valid;	/* set by driver if pt is current */
		struct  pt_info {
			s32		pi_nblocks; /* no. of sectors */
			u32		pi_blkoff;  /* block offset for start */
		} pt_part[8];
	} *label;

#define PT_MAGIC	0x032957	/* Partition magic number */
#define PT_VALID	1		/* Indicates if struct is valid */

	data = read_part_sector(state, (16384 - sizeof(*label))/512, &sect);
	if (!data)
		return -1;
	
	label = (struct ultrix_disklabel *)(data + 512 - sizeof(*label));

	if (label->pt_magic == PT_MAGIC && label->pt_valid == PT_VALID) {
		for (i=0; i<8; i++)
			if (label->pt_part[i].pi_nblocks)
				put_partition(state, i+1, 
					      label->pt_part[i].pi_blkoff,
					      label->pt_part[i].pi_nblocks);
		put_dev_sector(sect);
		strlcat(state->pp_buf, "\n", PAGE_SIZE);
		return 1;
	} else {
		put_dev_sector(sect);
		return 0;
	}
}
