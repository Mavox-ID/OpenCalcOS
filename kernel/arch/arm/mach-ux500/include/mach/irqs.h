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
#ifndef ASM_ARCH_IRQS_H
#define ASM_ARCH_IRQS_H

#include <mach/hardware.h>

#define IRQ_LOCALTIMER			29
#define IRQ_LOCALWDOG			30

/* Shared Peripheral Interrupt (SHPI) */
#define IRQ_SHPI_START			32

/*
 * MTU0 preserved for now until plat-nomadik is taught not to use it.  Don't
 * add any other IRQs here, use the irqs-dbx500.h files.
 */
#define IRQ_MTU0		(IRQ_SHPI_START + 4)

#define DBX500_NR_INTERNAL_IRQS		166

/* After chip-specific IRQ numbers we have the GPIO ones */
#define NOMADIK_NR_GPIO			288
#define NOMADIK_GPIO_TO_IRQ(gpio)	((gpio) + DBX500_NR_INTERNAL_IRQS)
#define NOMADIK_IRQ_TO_GPIO(irq)	((irq) - DBX500_NR_INTERNAL_IRQS)
#define IRQ_GPIO_END			NOMADIK_GPIO_TO_IRQ(NOMADIK_NR_GPIO)

#define IRQ_SOC_START		IRQ_GPIO_END
/* This will be overridden by SoC-specific irq headers */
#define IRQ_SOC_END		IRQ_SOC_START

#include <mach/irqs-db8500.h>

#define IRQ_BOARD_START		IRQ_SOC_END
/* This will be overridden by board-specific irq headers */
#define IRQ_BOARD_END		IRQ_BOARD_START

#ifdef CONFIG_MACH_MOP500
#include <mach/irqs-board-mop500.h>
#endif

#define UX500_NR_IRQS		IRQ_BOARD_END

#endif /* ASM_ARCH_IRQS_H */
