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
#ifndef __ARCH_ARM_MACH_VT8500_DT_COMMON_H
#define __ARCH_ARM_MACH_VT8500_DT_COMMON_H

#include <beep/of.h>

void __init vt8500_timer_init(void);
int __init vt8500_irq_init(struct device_node *node,
				struct device_node *parent);

/* defined in drivers/clk/clk-vt8500.c */
void __init vtwm_clk_init(void __iomem *pmc_base);

/* defined in irq.c */
asmlinkage void vt8500_handle_irq(struct pt_regs *regs);

#endif
