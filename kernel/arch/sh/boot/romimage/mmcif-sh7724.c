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
#include <beep/mmc/sh_mmcif.h>
#include <beep/mmc/boot.h>
#include <mach/romimage.h>

#define MMCIF_BASE      (void __iomem *)0xa4ca0000

#define MSTPCR2		0xa4150038
#define PTWCR		0xa4050146
#define PTXCR		0xa4050148
#define PSELA		0xa405014e
#define PSELE		0xa4050156
#define HIZCRC		0xa405015c
#define DRVCRA		0xa405018a

/* SH7724 specific MMCIF loader
 *
 * loads the romImage from an MMC card starting from block 512
 * use the following line to write the romImage to an MMC card
 * # dd if=arch/sh/boot/romImage of=/dev/sdx bs=512 seek=512
 */
asmlinkage void mmcif_loader(unsigned char *buf, unsigned long no_bytes)
{
	mmcif_update_progress(MMC_PROGRESS_ENTER);

	/* enable clock to the MMCIF hardware block */
	__raw_writel(__raw_readl(MSTPCR2) & ~0x20000000, MSTPCR2);

	/* setup pins D7-D0 */
	__raw_writew(0x0000, PTWCR);

	/* setup pins MMC_CLK, MMC_CMD */
	__raw_writew(__raw_readw(PTXCR) & ~0x000f, PTXCR);

	/* select D3-D0 pin function */
	__raw_writew(__raw_readw(PSELA) & ~0x2000, PSELA);

	/* select D7-D4 pin function */
	__raw_writew(__raw_readw(PSELE) & ~0x3000, PSELE);

	/* disable Hi-Z for the MMC pins */
	__raw_writew(__raw_readw(HIZCRC) & ~0x0620, HIZCRC);

	/* high drive capability for MMC pins */
	__raw_writew(__raw_readw(DRVCRA) | 0x3000, DRVCRA);

	mmcif_update_progress(MMC_PROGRESS_INIT);

	/* setup MMCIF hardware */
	sh_mmcif_boot_init(MMCIF_BASE);

	mmcif_update_progress(MMC_PROGRESS_LOAD);

	/* load kernel via MMCIF interface */
	sh_mmcif_boot_do_read(MMCIF_BASE, 512,
	                      (no_bytes + SH_MMCIF_BBS - 1) / SH_MMCIF_BBS,
			      buf);

	/* disable clock to the MMCIF hardware block */
	__raw_writel(__raw_readl(MSTPCR2) | 0x20000000, MSTPCR2);

	mmcif_update_progress(MMC_PROGRESS_DONE);
}
