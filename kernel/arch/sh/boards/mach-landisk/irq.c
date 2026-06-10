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
#include <beep/interrupt.h>
#include <beep/io.h>
#include <mach-landisk/mach/iodata_landisk.h>

enum {
	UNUSED = 0,

	PCI_INTA, /* PCI int A */
	PCI_INTB, /* PCI int B */
	PCI_INTC, /* PCI int C */
	PCI_INTD, /* PCI int D */
	ATA,	  /* ATA */
	FATA,	  /* CF */
	POWER,	  /* Power swtich */
	BUTTON,	  /* Button swtich */
};

/* Vectors for LANDISK */
static struct intc_vect vectors_landisk[] __initdata = {
	INTC_IRQ(PCI_INTA, IRQ_PCIINTA),
	INTC_IRQ(PCI_INTB, IRQ_PCIINTB),
	INTC_IRQ(PCI_INTC, IRQ_PCIINTC),
	INTC_IRQ(PCI_INTD, IRQ_PCIINTD),
	INTC_IRQ(ATA, IRQ_ATA),
	INTC_IRQ(FATA, IRQ_FATA),
	INTC_IRQ(POWER, IRQ_POWER),
	INTC_IRQ(BUTTON, IRQ_BUTTON),
};

/* IRLMSK mask register layout for LANDISK */
static struct intc_mask_reg mask_registers_landisk[] __initdata = {
	{ PA_IMASK, 0, 8, /* IRLMSK */
	  {  BUTTON, POWER, FATA, ATA,
	     PCI_INTD, PCI_INTC, PCI_INTB, PCI_INTA,
	  }
	},
};

static DECLARE_INTC_DESC(intc_desc_landisk, "landisk", vectors_landisk, NULL,
			mask_registers_landisk, NULL, NULL);
/*
 * Initialize IRQ setting
 */
void __init init_landisk_IRQ(void)
{
	register_intc_controller(&intc_desc_landisk);
	__raw_writeb(0x00, PA_PWRINT_CLR);
}
