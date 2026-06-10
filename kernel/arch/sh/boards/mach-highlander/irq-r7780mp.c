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
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/io.h>
#include <mach/highlander.h>

enum {
	UNUSED = 0,

	/* board specific interrupt sources */
	CF,		/* Compact Flash */
	TP,		/* Touch panel */
	SCIF1,		/* FPGA SCIF1 */
	SCIF0,		/* FPGA SCIF0 */
	SMBUS,		/* SMBUS */
	RTC,		/* RTC Alarm */
	AX88796,	/* Ethernet controller */
	PSW,		/* Push Switch */

	/* external bus connector */
	EXT1, EXT2, EXT4, EXT5, EXT6,
};

static struct intc_vect vectors[] __initdata = {
	INTC_IRQ(CF, IRQ_CF),
	INTC_IRQ(TP, IRQ_TP),
	INTC_IRQ(SCIF1, IRQ_SCIF1),
	INTC_IRQ(SCIF0, IRQ_SCIF0),
	INTC_IRQ(SMBUS, IRQ_SMBUS),
	INTC_IRQ(RTC, IRQ_RTC),
	INTC_IRQ(AX88796, IRQ_AX88796),
	INTC_IRQ(PSW, IRQ_PSW),

	INTC_IRQ(EXT1, IRQ_EXT1), INTC_IRQ(EXT2, IRQ_EXT2),
	INTC_IRQ(EXT4, IRQ_EXT4), INTC_IRQ(EXT5, IRQ_EXT5),
	INTC_IRQ(EXT6, IRQ_EXT6),
};

static struct intc_mask_reg mask_registers[] __initdata = {
	{ 0xa4000000, 0, 16, /* IRLMSK */
	  { SCIF0, SCIF1, RTC, 0, CF, 0, TP, SMBUS,
	    0, EXT6, EXT5, EXT4, EXT2, EXT1, PSW, AX88796 } },
};

static unsigned char irl2irq[HL_NR_IRL] __initdata = {
	0, IRQ_CF, IRQ_TP, IRQ_SCIF1,
	IRQ_SCIF0, IRQ_SMBUS, IRQ_RTC, IRQ_EXT6,
	IRQ_EXT5, IRQ_EXT4, IRQ_EXT2, IRQ_EXT1,
	0, IRQ_AX88796, IRQ_PSW,
};

static DECLARE_INTC_DESC(intc_desc, "r7780mp", vectors,
			 NULL, mask_registers, NULL, NULL);

unsigned char * __init highlander_plat_irq_setup(void)
{
	if ((__raw_readw(0xa4000700) & 0xf000) == 0x2000) {
		printk(KERN_INFO "Using r7780mp interrupt controller.\n");
		register_intc_controller(&intc_desc);
		return irl2irq;
	}

	return NULL;
}
