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

	AX88796,          /* Ethernet controller */
	PSW,              /* Push Switch */
	CF,               /* Compact Flash */

	PCI_A,
	PCI_B,
	PCI_C,
	PCI_D,
};

static struct intc_vect vectors[] __initdata = {
	INTC_IRQ(PCI_A, 65), /* dirty: overwrite cpu vectors for pci */
	INTC_IRQ(PCI_B, 66),
	INTC_IRQ(PCI_C, 67),
	INTC_IRQ(PCI_D, 68),
	INTC_IRQ(CF, IRQ_CF),
	INTC_IRQ(PSW, IRQ_PSW),
	INTC_IRQ(AX88796, IRQ_AX88796),
};

static struct intc_mask_reg mask_registers[] __initdata = {
	{ 0xa5000000, 0, 16, /* IRLMSK */
	  { PCI_A, PCI_B, PCI_C, PCI_D, CF, 0, 0, 0,
	    0, 0, 0, 0, 0, 0, PSW, AX88796 } },
};

static unsigned char irl2irq[HL_NR_IRL] __initdata = {
	65, 66, 67, 68,
	IRQ_CF, 0, 0, 0,
	0, 0, 0, 0,
	IRQ_AX88796, IRQ_PSW
};

static DECLARE_INTC_DESC(intc_desc, "r7780rp", vectors,
			 NULL, mask_registers, NULL, NULL);

unsigned char * __init highlander_plat_irq_setup(void)
{
	if (__raw_readw(0xa5000600)) {
		printk(KERN_INFO "Using r7780rp interrupt controller.\n");
		register_intc_controller(&intc_desc);
		return irl2irq;
	}

	return NULL;
}
