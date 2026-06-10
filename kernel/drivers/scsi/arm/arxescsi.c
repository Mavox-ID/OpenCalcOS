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
#include <beep/module.h>
#include <beep/blkdev.h>
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/ioport.h>
#include <beep/proc_fs.h>
#include <beep/unistd.h>
#include <beep/stat.h>
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/interrupt.h>

#include <asm/dma.h>
#include <asm/io.h>
#include <asm/ecard.h>

#include "../scsi.h"
#include <scsi/scsi_host.h>
#include "fas216.h"

struct arxescsi_info {
	FAS216_Info		info;
	struct expansion_card	*ec;
	void __iomem		*base;
};

#define DMADATA_OFFSET	(0x200)

#define DMASTAT_OFFSET	(0x600)
#define DMASTAT_DRQ	(1 << 0)

#define CSTATUS_IRQ	(1 << 0)

#define VERSION "1.10 (23/01/2003 2.5.57)"

/*
 * Function: int arxescsi_dma_setup(host, SCpnt, direction, min_type)
 * Purpose : initialises DMA/PIO
 * Params  : host      - host
 *	     SCpnt     - command
 *	     direction - DMA on to/off of card
 *	     min_type  - minimum DMA support that we must have for this transfer
 * Returns : 0 if we should not set CMD_WITHDMA for transfer info command
 */
static fasdmatype_t
arxescsi_dma_setup(struct Scsi_Host *host, struct scsi_pointer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
{
	/*
	 * We don't do real DMA
	 */
	return fasdma_pseudo;
}

static void arxescsi_pseudo_dma_write(unsigned char *addr, void __iomem *base)
{
       __asm__ __volatile__(
       "               stmdb   sp!, {r0-r12}\n"
       "               mov     r3, %0\n"
       "               mov     r1, %1\n"
       "               add     r2, r1, #512\n"
       "               mov     r4, #256\n"
       ".loop_1:       ldmia   r3!, {r6, r8, r10, r12}\n"
       "               mov     r5, r6, lsl #16\n"
       "               mov     r7, r8, lsl #16\n"
       ".loop_2:       ldrb    r0, [r1, #1536]\n"
       "               tst     r0, #1\n"
       "               beq     .loop_2\n"
       "               stmia   r2, {r5-r8}\n\t"
       "               mov     r9, r10, lsl #16\n"
       "               mov     r11, r12, lsl #16\n"
       ".loop_3:       ldrb    r0, [r1, #1536]\n"
       "               tst     r0, #1\n"
       "               beq     .loop_3\n"
       "               stmia   r2, {r9-r12}\n"
       "               subs    r4, r4, #16\n"
       "               bne     .loop_1\n"
       "               ldmia   sp!, {r0-r12}\n"
       :
       : "r" (addr), "r" (base));
}

/*
 * Function: int arxescsi_dma_pseudo(host, SCpnt, direction, transfer)
 * Purpose : handles pseudo DMA
 * Params  : host      - host
 *	     SCpnt     - command
 *	     direction - DMA on to/off of card
 *	     transfer  - minimum number of bytes we expect to transfer
 */
static void
arxescsi_dma_pseudo(struct Scsi_Host *host, struct scsi_pointer *SCp,
		    fasdmadir_t direction, int transfer)
{
	struct arxescsi_info *info = (struct arxescsi_info *)host->hostdata;
	unsigned int length, error = 0;
	void __iomem *base = info->info.scsi.io_base;
	unsigned char *addr;

	length = SCp->this_residual;
	addr = SCp->ptr;

	if (direction == DMA_OUT) {
		unsigned int word;
		while (length > 256) {
			if (readb(base + 0x80) & STAT_INT) {
				error = 1;
				break;
			}
			arxescsi_pseudo_dma_write(addr, base);
			addr += 256;
			length -= 256;
		}

		if (!error)
			while (length > 0) {
				if (readb(base + 0x80) & STAT_INT)
					break;
	 
				if (!(readb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					continue;

				word = *addr | *(addr + 1) << 8;

				writew(word, base + DMADATA_OFFSET);
				if (length > 1) {
					addr += 2;
					length -= 2;
				} else {
					addr += 1;
					length -= 1;
				}
			}
	}
	else {
		if (transfer && (transfer & 255)) {
			while (length >= 256) {
				if (readb(base + 0x80) & STAT_INT) {
					error = 1;
					break;
				}
	    
				if (!(readb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					continue;

				readsw(base + DMADATA_OFFSET, addr, 256 >> 1);
				addr += 256;
				length -= 256;
			}
		}

		if (!(error))
			while (length > 0) {
				unsigned long word;

				if (readb(base + 0x80) & STAT_INT)
					break;

				if (!(readb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					continue;

				word = readw(base + DMADATA_OFFSET);
				*addr++ = word;
				if (--length > 0) {
					*addr++ = word >> 8;
					length --;
				}
			}
	}
}

/*
 * Function: int arxescsi_dma_stop(host, SCpnt)
 * Purpose : stops DMA/PIO
 * Params  : host  - host
 *	     SCpnt - command
 */
static void arxescsi_dma_stop(struct Scsi_Host *host, struct scsi_pointer *SCp)
{
	/*
	 * no DMA to stop
	 */
}

/*
 * Function: const char *arxescsi_info(struct Scsi_Host * host)
 * Purpose : returns a descriptive string about this interface,
 * Params  : host - driver host structure to return info for.
 * Returns : pointer to a static buffer containing null terminated string.
 */
static const char *arxescsi_info(struct Scsi_Host *host)
{
	struct arxescsi_info *info = (struct arxescsi_info *)host->hostdata;
	static char string[150];

	sprintf(string, "%s (%s) in slot %d v%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION);

	return string;
}

/*
 * Function: int arxescsi_proc_info(char *buffer, char **start, off_t offset,
 *					 int length, int host_no, int inout)
 * Purpose : Return information about the driver to a user process accessing
 *	     the /proc filesystem.
 * Params  : buffer - a buffer to write information to
 *	     start  - a pointer into this buffer set by this routine to the start
 *		      of the required information.
 *	     offset - offset into information that we have read up to.
 *	     length - length of buffer
 *	     host_no - host number to return information for
 *	     inout  - 0 for reading, 1 for writing.
 * Returns : length of data written to buffer.
 */
static int
arxescsi_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset, int length,
		   int inout)
{
	struct arxescsi_info *info;
	char *p = buffer;
	int pos;

	info = (struct arxescsi_info *)host->hostdata;
	if (inout == 1)
		return -EINVAL;

	p += sprintf(p, "ARXE 16-bit SCSI driver v%s\n", VERSION);
	p += fas216_print_host(&info->info, p);
	p += fas216_print_stats(&info->info, p);
	p += fas216_print_devices(&info->info, p);

	*start = buffer + offset;
	pos = p - buffer - offset;
	if (pos > length)
		pos = length;

	return pos;
}

static struct scsi_host_template arxescsi_template = {
	.proc_info			= arxescsi_proc_info,
	.name				= "ARXE SCSI card",
	.info				= arxescsi_info,
	.queuecommand			= fas216_noqueue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_abort_handler		= fas216_eh_abort,
	.can_queue			= 0,
	.this_id			= 7,
	.sg_tablesize			= SG_ALL,
	.cmd_per_lun			= 1,
	.use_clustering			= DISABLE_CLUSTERING,
	.proc_name			= "arxescsi",
};

static int arxescsi_probe(struct expansion_card *ec, const struct ecard_id *id)
{
	struct Scsi_Host *host;
	struct arxescsi_info *info;
	void __iomem *base;
	int ret;

	ret = ecard_request_resources(ec);
	if (ret)
		goto out;

	base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	if (!base) {
		ret = -ENOMEM;
		goto out_region;
	}

	host = scsi_host_alloc(&arxescsi_template, sizeof(struct arxescsi_info));
	if (!host) {
		ret = -ENOMEM;
		goto out_region;
	}

	info = (struct arxescsi_info *)host->hostdata;
	info->ec = ec;
	info->base = base;

	info->info.scsi.io_base		= base + 0x2000;
	info->info.scsi.irq		= 0;
	info->info.scsi.dma		= NO_DMA;
	info->info.scsi.io_shift	= 5;
	info->info.ifcfg.clockrate	= 24; /* MHz */
	info->info.ifcfg.select_timeout = 255;
	info->info.ifcfg.asyncperiod	= 200; /* ns */
	info->info.ifcfg.sync_max_depth	= 0;
	info->info.ifcfg.cntl3		= CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.ifcfg.disconnect_ok	= 0;
	info->info.ifcfg.wide_max_size	= 0;
	info->info.ifcfg.capabilities	= FASCAP_PSEUDODMA;
	info->info.dma.setup		= arxescsi_dma_setup;
	info->info.dma.pseudo		= arxescsi_dma_pseudo;
	info->info.dma.stop		= arxescsi_dma_stop;
		
	ec->irqaddr = base;
	ec->irqmask = CSTATUS_IRQ;

	ret = fas216_init(host);
	if (ret)
		goto out_unregister;

	ret = fas216_add(host, &ec->dev);
	if (ret == 0)
		goto out;

	fas216_release(host);
 out_unregister:
	scsi_host_put(host);
 out_region:
	ecard_release_resources(ec);
 out:
	return ret;
}

static void arxescsi_remove(struct expansion_card *ec)
{
	struct Scsi_Host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, NULL);
	fas216_remove(host);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
}

static const struct ecard_id arxescsi_cids[] = {
	{ MANU_ARXE, PROD_ARXE_SCSI },
	{ 0xffff, 0xffff },
};

static struct ecard_driver arxescsi_driver = {
	.probe		= arxescsi_probe,
	.remove		= arxescsi_remove,
	.id_table	= arxescsi_cids,
	.drv = {
		.name		= "arxescsi",
	},
};

static int __init init_arxe_scsi_driver(void)
{
	return ecard_register_driver(&arxescsi_driver);
}

static void __exit exit_arxe_scsi_driver(void)
{
	ecard_remove_driver(&arxescsi_driver);
}

module_init(init_arxe_scsi_driver);
module_exit(exit_arxe_scsi_driver);

MODULE_AUTHOR("Stefan Hanske");
MODULE_DESCRIPTION("ARXESCSI driver for Acorn machines");
MODULE_LICENSE("GPL");

