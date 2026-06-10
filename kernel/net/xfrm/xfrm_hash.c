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
#include <beep/kernel.h>
#include <beep/mm.h>
#include <beep/bootmem.h>
#include <beep/vmalloc.h>
#include <beep/slab.h>
#include <beep/xfrm.h>

#include "xfrm_hash.h"

struct hlist_head *xfrm_hash_alloc(unsigned int sz)
{
	struct hlist_head *n;

	if (sz <= PAGE_SIZE)
		n = kzalloc(sz, GFP_KERNEL);
	else if (hashdist)
		n = vzalloc(sz);
	else
		n = (struct hlist_head *)
			__get_free_pages(GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO,
					 get_order(sz));

	return n;
}

void xfrm_hash_free(struct hlist_head *n, unsigned int sz)
{
	if (sz <= PAGE_SIZE)
		kfree(n);
	else if (hashdist)
		vfree(n);
	else
		free_pages((unsigned long)n, get_order(sz));
}
