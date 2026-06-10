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
#ifndef _NLM_HAL_XLP_H
#define _NLM_HAL_XLP_H

#define PIC_UART_0_IRQ			17
#define PIC_UART_1_IRQ			18
#define PIC_PCIE_LINK_0_IRQ		19
#define PIC_PCIE_LINK_1_IRQ		20
#define PIC_PCIE_LINK_2_IRQ		21
#define PIC_PCIE_LINK_3_IRQ		22
#define PIC_EHCI_0_IRQ			23
#define PIC_EHCI_1_IRQ			24
#define PIC_OHCI_0_IRQ			25
#define PIC_OHCI_1_IRQ			26
#define PIC_OHCI_2_IRQ			27
#define PIC_OHCI_3_IRQ			28
#define PIC_MMC_IRQ			29
#define PIC_I2C_0_IRQ			30
#define PIC_I2C_1_IRQ			31

#ifndef __ASSEMBLY__

/* SMP support functions */
void xlp_boot_core0_siblings(void);
void xlp_wakeup_secondary_cpus(void);

void xlp_mmu_init(void);
void nlm_hal_init(void);

#endif /* !__ASSEMBLY__ */
#endif /* _ASM_NLM_XLP_H */
