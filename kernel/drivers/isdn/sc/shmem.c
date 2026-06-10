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
#include "includes.h"		/* This must be first */
#include "hardware.h"
#include "card.h"

/*
 *
 */
void memcpy_toshmem(int card, void *dest, const void *src, size_t n)
{
	unsigned long flags;
	unsigned char ch;
	unsigned long dest_rem = ((unsigned long) dest) % 0x4000;

	if (!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return;
	}

	if (n > SRAM_PAGESIZE)
		return;

	/*
	 * determine the page to load from the address
	 */
	ch = (unsigned long) dest / SRAM_PAGESIZE;
	pr_debug("%s: loaded page %d\n", sc_adapter[card]->devicename, ch);
	/*
	 * Block interrupts and load the page
	 */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);

	outb(((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80,
	     sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport]);
	memcpy_toio((void __iomem *)(sc_adapter[card]->rambase + dest_rem), src, n);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
	pr_debug("%s: set page to %#x\n", sc_adapter[card]->devicename,
		 ((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80);
	pr_debug("%s: copying %zu bytes from %#lx to %#lx\n",
		 sc_adapter[card]->devicename, n,
		 (unsigned long) src,
		 sc_adapter[card]->rambase + ((unsigned long) dest % 0x4000));
}

/*
 * Reverse of above
 */
void memcpy_fromshmem(int card, void *dest, const void *src, size_t n)
{
	unsigned long flags;
	unsigned char ch;

	if (!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return;
	}

	if (n > SRAM_PAGESIZE) {
		return;
	}

	/*
	 * determine the page to load from the address
	 */
	ch = (unsigned long) src / SRAM_PAGESIZE;
	pr_debug("%s: loaded page %d\n", sc_adapter[card]->devicename, ch);


	/*
	 * Block interrupts and load the page
	 */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);

	outb(((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80,
	     sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport]);
	memcpy_fromio(dest, (void *)(sc_adapter[card]->rambase +
				     ((unsigned long) src % 0x4000)), n);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
	pr_debug("%s: set page to %#x\n", sc_adapter[card]->devicename,
		 ((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80);
/*	pr_debug("%s: copying %d bytes from %#x to %#x\n",
	sc_adapter[card]->devicename, n,
	sc_adapter[card]->rambase + ((unsigned long) src %0x4000), (unsigned long) dest); */
}

#if 0
void memset_shmem(int card, void *dest, int c, size_t n)
{
	unsigned long flags;
	unsigned char ch;

	if (!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return;
	}

	if (n > SRAM_PAGESIZE) {
		return;
	}

	/*
	 * determine the page to load from the address
	 */
	ch = (unsigned long) dest / SRAM_PAGESIZE;
	pr_debug("%s: loaded page %d\n", sc_adapter[card]->devicename, ch);

	/*
	 * Block interrupts and load the page
	 */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);

	outb(((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80,
	     sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport]);
	memset_io(sc_adapter[card]->rambase +
		  ((unsigned long) dest % 0x4000), c, n);
	pr_debug("%s: set page to %#x\n", sc_adapter[card]->devicename,
		 ((sc_adapter[card]->shmem_magic + ch * SRAM_PAGESIZE) >> 14) | 0x80);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
}
#endif  /*  0  */
