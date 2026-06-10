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
#include <beep/ioport.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/screen_info.h>
#include <beep/io.h>
#include <beep/spinlock.h>

#include <asm/hardware/dec21285.h>
#include <asm/mach-types.h>
#include <asm/setup.h>

#include <asm/mach/arch.h>

#include "common.h"

#define CFG_PORT	0x370
#define INDEX_PORT	(CFG_PORT)
#define DATA_PORT	(CFG_PORT + 1)

static int __init cats_hw_init(void)
{
	if (machine_is_cats()) {
		/* Set Aladdin to CONFIGURE mode */
		outb(0x51, CFG_PORT);
		outb(0x23, CFG_PORT);

		/* Select logical device 3 */
		outb(0x07, INDEX_PORT);
		outb(0x03, DATA_PORT);

		/* Set parallel port to DMA channel 3, ECP+EPP1.9, 
		   enable EPP timeout */
		outb(0x74, INDEX_PORT);
		outb(0x03, DATA_PORT);
	
		outb(0xf0, INDEX_PORT);
		outb(0x0f, DATA_PORT);

		outb(0xf1, INDEX_PORT);
		outb(0x07, DATA_PORT);

		/* Select logical device 4 */
		outb(0x07, INDEX_PORT);
		outb(0x04, DATA_PORT);

		/* UART1 high speed mode */
		outb(0xf0, INDEX_PORT);
		outb(0x02, DATA_PORT);

		/* Select logical device 5 */
		outb(0x07, INDEX_PORT);
		outb(0x05, DATA_PORT);

		/* UART2 high speed mode */
		outb(0xf0, INDEX_PORT);
		outb(0x02, DATA_PORT);

		/* Set Aladdin to RUN mode */
		outb(0xbb, CFG_PORT);
	}

	return 0;
}

__initcall(cats_hw_init);

/*
 * CATS uses soft-reboot by default, since
 * hard reboots fail on early boards.
 */
static void __init
fixup_cats(struct tag *tags, char **cmdline, struct meminfo *mi)
{
	screen_info.orig_video_lines  = 25;
	screen_info.orig_video_points = 16;
	screen_info.orig_y = 24;
}

MACHINE_START(CATS, "Chalice-CATS")
	/* Maintainer: Philip Blundell */
	.atag_offset	= 0x100,
	.restart_mode	= 's',
	.fixup		= fixup_cats,
	.map_io		= footbridge_map_io,
	.init_irq	= footbridge_init_irq,
	.timer		= &isa_timer,
	.restart	= footbridge_restart,
MACHINE_END
