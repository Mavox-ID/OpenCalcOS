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
#ifndef _ASM_BFIN_PCI_H
#define _ASM_BFIN_PCI_H

#include <asm/scatterlist.h>
#include <asm-generic/pci-dma-compat.h>
#include <asm-generic/pci.h>

#define PCIBIOS_MIN_IO 0x00001000
#define PCIBIOS_MIN_MEM 0x10000000

static inline void pcibios_penalize_isa_irq(int irq)
{
	/* We don't do dynamic PCI IRQ allocation */
}

#endif				/* _ASM_BFIN_PCI_H */
