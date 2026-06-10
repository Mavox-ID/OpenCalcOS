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
#include <beep/bio.h>
#include <beep/kernel.h>
#include <beep/pagemap.h>
#include <beep/swap.h>

#include "power.h"

/**
 *	submit - submit BIO request.
 *	@rw:	READ or WRITE.
 *	@off	physical offset of page.
 *	@page:	page we're reading or writing.
 *	@bio_chain: list of pending biod (for async reading)
 *
 *	Straight from the textbook - allocate and initialize the bio.
 *	If we're reading, make sure the page is marked as dirty.
 *	Then submit it and, if @bio_chain == NULL, wait.
 */
static int submit(int rw, struct block_device *bdev, sector_t sector,
		struct page *page, struct bio **bio_chain)
{
	const int bio_rw = rw | REQ_SYNC;
	struct bio *bio;

	bio = bio_alloc(__GFP_WAIT | __GFP_HIGH, 1);
	bio->bi_sector = sector;
	bio->bi_bdev = bdev;
	bio->bi_end_io = end_swap_bio_read;

	if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) {
		printk(KERN_ERR "PM: Adding page to bio failed at %llu\n",
			(unsigned long long)sector);
		bio_put(bio);
		return -EFAULT;
	}

	lock_page(page);
	bio_get(bio);

	if (bio_chain == NULL) {
		submit_bio(bio_rw, bio);
		wait_on_page_locked(page);
		if (rw == READ)
			bio_set_pages_dirty(bio);
		bio_put(bio);
	} else {
		if (rw == READ)
			get_page(page);	/* These pages are freed later */
		bio->bi_private = *bio_chain;
		*bio_chain = bio;
		submit_bio(bio_rw, bio);
	}
	return 0;
}

int hib_bio_read_page(pgoff_t page_off, void *addr, struct bio **bio_chain)
{
	return submit(READ, hib_resume_bdev, page_off * (PAGE_SIZE >> 9),
			virt_to_page(addr), bio_chain);
}

int hib_bio_write_page(pgoff_t page_off, void *addr, struct bio **bio_chain)
{
	return submit(WRITE, hib_resume_bdev, page_off * (PAGE_SIZE >> 9),
			virt_to_page(addr), bio_chain);
}

int hib_wait_on_bio_chain(struct bio **bio_chain)
{
	struct bio *bio;
	struct bio *next_bio;
	int ret = 0;

	if (bio_chain == NULL)
		return 0;

	bio = *bio_chain;
	if (bio == NULL)
		return 0;
	while (bio) {
		struct page *page;

		next_bio = bio->bi_private;
		page = bio->bi_io_vec[0].bv_page;
		wait_on_page_locked(page);
		if (!PageUptodate(page) || PageError(page))
			ret = -EIO;
		put_page(page);
		bio_put(bio);
		bio = next_bio;
	}
	*bio_chain = NULL;
	return ret;
}
