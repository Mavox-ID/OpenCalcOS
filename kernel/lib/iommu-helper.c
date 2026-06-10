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
#include <beep/export.h>
#include <beep/bitmap.h>
#include <beep/bug.h>

int iommu_is_span_boundary(unsigned int index, unsigned int nr,
			   unsigned long shift,
			   unsigned long boundary_size)
{
	BUG_ON(!is_power_of_2(boundary_size));

	shift = (shift + index) & (boundary_size - 1);
	return shift + nr > boundary_size;
}

unsigned long iommu_area_alloc(unsigned long *map, unsigned long size,
			       unsigned long start, unsigned int nr,
			       unsigned long shift, unsigned long boundary_size,
			       unsigned long align_mask)
{
	unsigned long index;

	/* We don't want the last of the limit */
	size -= 1;
again:
	index = bitmap_find_next_zero_area(map, size, start, nr, align_mask);
	if (index < size) {
		if (iommu_is_span_boundary(index, nr, shift, boundary_size)) {
			/* we could do more effectively */
			start = index + 1;
			goto again;
		}
		bitmap_set(map, index, nr);
		return index;
	}
	return -1;
}
EXPORT_SYMBOL(iommu_area_alloc);
