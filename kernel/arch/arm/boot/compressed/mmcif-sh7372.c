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
#include <mach/mmc.h>

#define MMCIF_BASE      (void __iomem *)0xe6bd0000

#define PORT84CR	(void __iomem *)0xe6050054
#define PORT85CR	(void __iomem *)0xe6050055
#define PORT86CR	(void __iomem *)0xe6050056
#define PORT87CR	(void __iomem *)0xe6050057
#define PORT88CR	(void __iomem *)0xe6050058
#define PORT89CR	(void __iomem *)0xe6050059
#define PORT90CR	(void __iomem *)0xe605005a
#define PORT91CR	(void __iomem *)0xe605005b
#define PORT92CR	(void __iomem *)0xe605005c
#define PORT99CR	(void __iomem *)0xe6050063

#define SMSTPCR3	(void __iomem *)0xe615013c

/* SH7372 specific MMCIF loader
 *
 * loads the zCalc from an MMC card starting from block 1.
 *
 * The image must be start with a vrl4 header and
 * the zCalc must start at offset 512 of the image. That is,
 * at block 2 (=byte 1024) on the media
 *
 * Use the following line to write the vrl4 formated zCalc
 * to an MMC card
 * # dd if=vrl4.out of=/dev/sdx bs=512 seek=1
 */
asmlinkage void mmc_loader(unsigned char *buf, unsigned long len)
{
	mmc_init_progress();
	mmc_update_progress(MMC_PROGRESS_ENTER);

	/* Initialise MMC
	 * registers: PORT84CR-PORT92CR
	 *            (MMCD0_0-MMCD0_7,MMCCMD0 Control)
	 * value: 0x04 - select function 4
	 */
	 __raw_writeb(0x04, PORT84CR);
	 __raw_writeb(0x04, PORT85CR);
	 __raw_writeb(0x04, PORT86CR);
	 __raw_writeb(0x04, PORT87CR);
	 __raw_writeb(0x04, PORT88CR);
	 __raw_writeb(0x04, PORT89CR);
	 __raw_writeb(0x04, PORT90CR);
	 __raw_writeb(0x04, PORT91CR);
	 __raw_writeb(0x04, PORT92CR);

	/* Initialise MMC
	 * registers: PORT99CR (MMCCLK0 Control)
	 * value: 0x10 | 0x04 - enable output | select function 4
	 */
	__raw_writeb(0x14, PORT99CR);

	/* Enable clock to MMC hardware block */
	__raw_writel(__raw_readl(SMSTPCR3) & ~(1 << 12), SMSTPCR3);

	mmc_update_progress(MMC_PROGRESS_INIT);

	/* setup MMCIF hardware */
	sh_mmcif_boot_init(MMCIF_BASE);

	mmc_update_progress(MMC_PROGRESS_LOAD);

	/* load kernel via MMCIF interface */
	sh_mmcif_boot_do_read(MMCIF_BASE, 2, /* Kernel is at block 2 */
			      (len + SH_MMCIF_BBS - 1) / SH_MMCIF_BBS, buf);


	/* Disable clock to MMC hardware block */
	__raw_writel(__raw_readl(SMSTPCR3) | (1 << 12), SMSTPCR3);

	mmc_update_progress(MMC_PROGRESS_DONE);
}
