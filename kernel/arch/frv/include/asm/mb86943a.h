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
#ifndef _ASM_MB86943A_H
#define _ASM_MB86943A_H

#include <asm/mb-regs.h>

#define __reg_MB86943_sl_ctl		*(volatile uint32_t *) (__region_CS1 + 0x00)

#define MB86943_SL_CTL_BUS_WIDTH_64	0x00000001
#define MB86943_SL_CTL_AS_HOST		0x00000002
#define MB86943_SL_CTL_DRCT_MASTER_SWAP	0x00000004
#define MB86943_SL_CTL_DRCT_SLAVE_SWAP	0x00000008
#define MB86943_SL_CTL_PCI_CONFIG_SWAP	0x00000010
#define MB86943_SL_CTL_ECS0_ENABLE	0x00000020
#define MB86943_SL_CTL_ECS1_ENABLE	0x00000040
#define MB86943_SL_CTL_ECS2_ENABLE	0x00000080

#define __reg_MB86943_ecs_ctl(N)	*(volatile uint32_t *) (__region_CS1 + 0x08 + (0x08*(N)))
#define __reg_MB86943_ecs_range(N)	*(volatile uint32_t *) (__region_CS1 + 0x20 + (0x10*(N)))
#define __reg_MB86943_ecs_base(N)	*(volatile uint32_t *) (__region_CS1 + 0x28 + (0x10*(N)))

#define __reg_MB86943_sl_pci_io_range	*(volatile uint32_t *) (__region_CS1 + 0x50)
#define __reg_MB86943_sl_pci_io_base	*(volatile uint32_t *) (__region_CS1 + 0x58)
#define __reg_MB86943_sl_pci_mem_range	*(volatile uint32_t *) (__region_CS1 + 0x60)
#define __reg_MB86943_sl_pci_mem_base	*(volatile uint32_t *) (__region_CS1 + 0x68)
#define __reg_MB86943_pci_sl_io_base	*(volatile uint32_t *) (__region_CS1 + 0x70)
#define __reg_MB86943_pci_sl_mem_base	*(volatile uint32_t *) (__region_CS1 + 0x78)

#define __reg_MB86943_pci_arbiter	*(volatile uint32_t *) (__region_CS2 + 0x01300014)
#define MB86943_PCIARB_EN		0x00000001

#endif /* _ASM_MB86943A_H */
