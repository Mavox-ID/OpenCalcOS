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
#ifndef __ASM_ARCH_BRIDGE_REGS_H
#define __ASM_ARCH_BRIDGE_REGS_H

#include <mach/orion5x.h>

#define CPU_CONF		(ORION5X_BRIDGE_VIRT_BASE + 0x100)

#define CPU_CTRL		(ORION5X_BRIDGE_VIRT_BASE + 0x104)

#define RSTOUTn_MASK		(ORION5X_BRIDGE_VIRT_BASE + 0x108)
#define WDT_RESET_OUT_EN	0x0002

#define CPU_SOFT_RESET		(ORION5X_BRIDGE_VIRT_BASE + 0x10c)

#define BRIDGE_CAUSE		(ORION5X_BRIDGE_VIRT_BASE + 0x110)

#define POWER_MNG_CTRL_REG	(ORION5X_BRIDGE_VIRT_BASE + 0x11C)

#define WDT_INT_REQ		0x0008

#define BRIDGE_INT_TIMER1_CLR	(~0x0004)

#define MAIN_IRQ_CAUSE		(ORION5X_BRIDGE_VIRT_BASE + 0x200)

#define MAIN_IRQ_MASK		(ORION5X_BRIDGE_VIRT_BASE + 0x204)

#define TIMER_VIRT_BASE		(ORION5X_BRIDGE_VIRT_BASE + 0x300)
#define TIMER_PHYS_BASE		(ORION5X_BRIDGE_PHYS_BASE + 0x300)
#endif
