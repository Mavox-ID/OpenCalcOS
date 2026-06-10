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
#include <beep/highmem.h>
#include <beep/module.h>

#include <asm/word-at-a-time.h>
#include <beep/sched.h>

/*
 * best effort, GUP based copy_from_user() that is NMI-safe
 */
unsigned long
copy_from_user_nmi(void *to, const void __user *from, unsigned long n)
{
	unsigned long offset, addr = (unsigned long)from;
	unsigned long size, len = 0;
	struct page *page;
	void *map;
	int ret;

	if (__range_not_ok(from, n, TASK_SIZE))
		return len;

	do {
		ret = __get_user_pages_fast(addr, 1, 0, &page);
		if (!ret)
			break;

		offset = addr & (PAGE_SIZE - 1);
		size = min(PAGE_SIZE - offset, n - len);

		map = kmap_atomic(page);
		memcpy(to, map+offset, size);
		kunmap_atomic(map);
		put_page(page);

		len  += size;
		to   += size;
		addr += size;

	} while (len < n);

	return len;
}
EXPORT_SYMBOL_GPL(copy_from_user_nmi);
