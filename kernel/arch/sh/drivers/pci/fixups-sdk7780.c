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
#include <beep/pci.h>
#include <beep/io.h>
#include <beep/sh_intc.h>
#include "pci-sh4.h"

#define IRQ_INTA	evt2irq(0xa20)
#define IRQ_INTB	evt2irq(0xa40)
#define IRQ_INTC	evt2irq(0xa60)
#define IRQ_INTD	evt2irq(0xa80)

/* IDSEL [16][17][18][19][20][21][22][23][24][25][26][27][28][29][30][31] */
static char sdk7780_irq_tab[4][16] __initdata = {
	/* INTA */
	{ IRQ_INTA, IRQ_INTD, IRQ_INTC, IRQ_INTD, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1, -1, -1 },
	/* INTB */
	{ IRQ_INTB, IRQ_INTA, -1, IRQ_INTA, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 },
	/* INTC */
	{ IRQ_INTC, IRQ_INTB, -1, IRQ_INTB, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1, -1 },
	/* INTD */
	{ IRQ_INTD, IRQ_INTC, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	  -1, -1, -1 },
};

int __init pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
{
       return sdk7780_irq_tab[pin-1][slot];
}
