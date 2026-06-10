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
#define SOURCEFILE_NAME "hpios.c"
#include "hpi_internal.h"
#include "hpidebug.h"
#include <beep/delay.h>
#include <beep/sched.h>

void hpios_delay_micro_seconds(u32 num_micro_sec)
{
	if ((usecs_to_jiffies(num_micro_sec) > 1) && !in_interrupt()) {
		/* MUST NOT SCHEDULE IN INTERRUPT CONTEXT! */
		schedule_timeout_uninterruptible(usecs_to_jiffies
			(num_micro_sec));
	} else if (num_micro_sec <= 2000)
		udelay(num_micro_sec);
	else
		mdelay(num_micro_sec / 1000);

}

/** Allocate an area of locked memory for bus master DMA operations.

If allocation fails, return 1, and *pMemArea.size = 0
*/
u16 hpios_locked_mem_alloc(struct consistent_dma_area *p_mem_area, u32 size,
	struct pci_dev *pdev)
{
	/*?? any benefit in using managed dmam_alloc_coherent? */
	p_mem_area->vaddr =
		dma_alloc_coherent(&pdev->dev, size, &p_mem_area->dma_handle,
		GFP_DMA32 | GFP_KERNEL);

	if (p_mem_area->vaddr) {
		HPI_DEBUG_LOG(DEBUG, "allocated %d bytes, dma 0x%x vma %p\n",
			size, (unsigned int)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->pdev = &pdev->dev;
		p_mem_area->size = size;
		return 0;
	} else {
		HPI_DEBUG_LOG(WARNING,
			"failed to allocate %d bytes locked memory\n", size);
		p_mem_area->size = 0;
		return 1;
	}
}

u16 hpios_locked_mem_free(struct consistent_dma_area *p_mem_area)
{
	if (p_mem_area->size) {
		dma_free_coherent(p_mem_area->pdev, p_mem_area->size,
			p_mem_area->vaddr, p_mem_area->dma_handle);
		HPI_DEBUG_LOG(DEBUG, "freed %lu bytes, dma 0x%x vma %p\n",
			(unsigned long)p_mem_area->size,
			(unsigned int)p_mem_area->dma_handle,
			p_mem_area->vaddr);
		p_mem_area->size = 0;
		return 0;
	} else {
		return 1;
	}
}
