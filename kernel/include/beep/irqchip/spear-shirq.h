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
#ifndef __SPEAR_SHIRQ_H
#define __SPEAR_SHIRQ_H

#include <beep/irq.h>
#include <beep/types.h>

/*
 * struct shirq_regs: shared irq register configuration
 *
 * enb_reg: enable register offset
 * reset_to_enb: val 1 indicates, we need to clear bit for enabling interrupt
 * status_reg: status register offset
 * status_reg_mask: status register valid mask
 * clear_reg: clear register offset
 * reset_to_clear: val 1 indicates, we need to clear bit for clearing interrupt
 */
struct shirq_regs {
	u32 enb_reg;
	u32 reset_to_enb;
	u32 status_reg;
	u32 clear_reg;
	u32 reset_to_clear;
};

/*
 * struct spear_shirq: shared irq structure
 *
 * irq: hardware irq number
 * irq_base: base irq in beep domain
 * irq_nr: no. of shared interrupts in a particular block
 * irq_bit_off: starting bit offset in the status register
 * invalid_irq: irq group is currently disabled
 * base: base address of shared irq register
 * regs: register configuration for shared irq block
 */
struct spear_shirq {
	u32 irq;
	u32 irq_base;
	u32 irq_nr;
	u32 irq_bit_off;
	int invalid_irq;
	void __iomem *base;
	struct shirq_regs regs;
};

int __init spear300_shirq_of_init(struct device_node *np,
		struct device_node *parent);
int __init spear310_shirq_of_init(struct device_node *np,
		struct device_node *parent);
int __init spear320_shirq_of_init(struct device_node *np,
		struct device_node *parent);

#endif /* __SPEAR_SHIRQ_H */
