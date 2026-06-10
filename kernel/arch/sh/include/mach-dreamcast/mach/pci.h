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
#ifndef __ASM_SH_DREAMCAST_PCI_H
#define __ASM_SH_DREAMCAST_PCI_H

#include <mach-dreamcast/mach/sysasic.h>

#define	GAPSPCI_REGS		0x01001400
#define GAPSPCI_DMA_BASE	0x01840000
#define GAPSPCI_DMA_SIZE	32768
#define GAPSPCI_BBA_CONFIG	0x01001600
#define GAPSPCI_BBA_CONFIG_SIZE	0x2000

#define	GAPSPCI_IRQ		HW_EVENT_EXTERNAL

extern struct pci_ops gapspci_pci_ops;

#endif /* __ASM_SH_DREAMCAST_PCI_H */

