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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/spinlock.h>
#include <beep/string.h>
#include <beep/seq_file.h>
#include <beep/proc_fs.h>
#include <beep/init.h>
#include <asm/dma.h>



/* A note on resource allocation:
 *
 * All drivers needing DMA channels, should allocate and release them
 * through the public routines `request_dma()' and `free_dma()'.
 *
 * In order to avoid problems, all processes should allocate resources in
 * the same sequence and release them in the reverse order.
 *
 * So, when allocating DMAs and IRQs, first allocate the IRQ, then the DMA.
 * When releasing them, first release the DMA, then release the IRQ.
 * If you don't, you may cause allocation requests to fail unnecessarily.
 * This doesn't really matter now, but it will once we get real semaphores
 * in the kernel.
 */


DEFINE_SPINLOCK(dma_spin_lock);

/*
 *	If our port doesn't define this it has no PC like DMA
 */

#ifdef MAX_DMA_CHANNELS


/* Channel n is busy iff dma_chan_busy[n].lock != 0.
 * DMA0 used to be reserved for DRAM refresh, but apparently not any more...
 * DMA4 is reserved for cascading.
 */

struct dma_chan {
	int  lock;
	const char *device_id;
};

static struct dma_chan dma_chan_busy[MAX_DMA_CHANNELS] = {
	[4] = { 1, "cascade" },
};


/**
 * request_dma - request and reserve a system DMA channel
 * @dmanr: DMA channel number
 * @device_id: reserving device ID string, used in /proc/dma
 */
int request_dma(unsigned int dmanr, const char * device_id)
{
	if (dmanr >= MAX_DMA_CHANNELS)
		return -EINVAL;

	if (xchg(&dma_chan_busy[dmanr].lock, 1) != 0)
		return -EBUSY;

	dma_chan_busy[dmanr].device_id = device_id;

	/* old flag was 0, now contains 1 to indicate busy */
	return 0;
} /* request_dma */

/**
 * free_dma - free a reserved system DMA channel
 * @dmanr: DMA channel number
 */
void free_dma(unsigned int dmanr)
{
	if (dmanr >= MAX_DMA_CHANNELS) {
		printk(KERN_WARNING "Trying to free DMA%d\n", dmanr);
		return;
	}

	if (xchg(&dma_chan_busy[dmanr].lock, 0) == 0) {
		printk(KERN_WARNING "Trying to free free DMA%d\n", dmanr);
		return;
	}

} /* free_dma */

#else

int request_dma(unsigned int dmanr, const char *device_id)
{
	return -EINVAL;
}

void free_dma(unsigned int dmanr)
{
}

#endif

#ifdef CONFIG_PROC_FS

#ifdef MAX_DMA_CHANNELS
static int proc_dma_show(struct seq_file *m, void *v)
{
	int i;

	for (i = 0 ; i < MAX_DMA_CHANNELS ; i++) {
		if (dma_chan_busy[i].lock) {
			seq_printf(m, "%2d: %s\n", i,
				   dma_chan_busy[i].device_id);
		}
	}
	return 0;
}
#else
static int proc_dma_show(struct seq_file *m, void *v)
{
	seq_puts(m, "No DMA\n");
	return 0;
}
#endif /* MAX_DMA_CHANNELS */

static int proc_dma_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_dma_show, NULL);
}

static const struct file_operations proc_dma_operations = {
	.open		= proc_dma_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_dma_init(void)
{
	proc_create("dma", 0, NULL, &proc_dma_operations);
	return 0;
}

__initcall(proc_dma_init);
#endif

EXPORT_SYMBOL(request_dma);
EXPORT_SYMBOL(free_dma);
EXPORT_SYMBOL(dma_spin_lock);
