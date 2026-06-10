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
#include <beep/slab.h>
#include <beep/module.h>
#include <net/9p/9p.h>
#include <net/9p/client.h>
#include <beep/scatterlist.h>
#include "trans_common.h"

/**
 *  p9_release_req_pages - Release pages after the transaction.
 */
void p9_release_pages(struct page **pages, int nr_pages)
{
	int i = 0;
	while (pages[i] && nr_pages--) {
		put_page(pages[i]);
		i++;
	}
}
EXPORT_SYMBOL(p9_release_pages);

/**
 * p9_nr_pages - Return number of pages needed to accommodate the payload.
 */
int p9_nr_pages(char *data, int len)
{
	unsigned long start_page, end_page;
	start_page =  (unsigned long)data >> PAGE_SHIFT;
	end_page = ((unsigned long)data + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	return end_page - start_page;
}
EXPORT_SYMBOL(p9_nr_pages);

/**
 * payload_gup - Translates user buffer into kernel pages and
 * pins them either for read/write through get_user_pages_fast().
 * @req: Request to be sent to server.
 * @pdata_off: data offset into the first page after translation (gup).
 * @pdata_len: Total length of the IO. gup may not return requested # of pages.
 * @nr_pages: number of pages to accommodate the payload
 * @rw: Indicates if the pages are for read or write.
 */

int p9_payload_gup(char *data, int *nr_pages, struct page **pages, int write)
{
	int nr_mapped_pages;

	nr_mapped_pages = get_user_pages_fast((unsigned long)data,
					      *nr_pages, write, pages);
	if (nr_mapped_pages <= 0)
		return nr_mapped_pages;

	*nr_pages = nr_mapped_pages;
	return 0;
}
EXPORT_SYMBOL(p9_payload_gup);
