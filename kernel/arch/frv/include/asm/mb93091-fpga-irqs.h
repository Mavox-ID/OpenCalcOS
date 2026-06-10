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
#ifndef _ASM_MB93091_FPGA_IRQS_H
#define _ASM_MB93091_FPGA_IRQS_H

#include <asm/irq.h>

#ifndef __ASSEMBLY__

/* IRQ IDs presented to drivers */
enum {
	IRQ_FPGA__UNUSED			= IRQ_BASE_FPGA,
	IRQ_FPGA_SYSINT_BUS_EXPANSION_1,
	IRQ_FPGA_SL_BUS_EXPANSION_2,
	IRQ_FPGA_PCI_INTD,
	IRQ_FPGA_PCI_INTC,
	IRQ_FPGA_PCI_INTB,
	IRQ_FPGA_PCI_INTA,
	IRQ_FPGA_SL_BUS_EXPANSION_7,
	IRQ_FPGA_SYSINT_BUS_EXPANSION_8,
	IRQ_FPGA_SL_BUS_EXPANSION_9,
	IRQ_FPGA_MB86943_PCI_INTA,
	IRQ_FPGA_MB86943_SLBUS_SIDE,
	IRQ_FPGA_RTL8029_INTA,
	IRQ_FPGA_SYSINT_BUS_EXPANSION_13,
	IRQ_FPGA_SL_BUS_EXPANSION_14,
	IRQ_FPGA_NMI,
};


#endif /* !__ASSEMBLY__ */

#endif /* _ASM_MB93091_FPGA_IRQS_H */
