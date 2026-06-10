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
#ifndef __ARCH_ARM_MACH_OMAP2_CLOCK3XXX_H
#define __ARCH_ARM_MACH_OMAP2_CLOCK3XXX_H

int omap3xxx_clk_init(void);
int omap3_dpll4_set_rate(struct clk_hw *clk, unsigned long rate,
					unsigned long parent_rate);
int omap3_core_dpll_m2_set_rate(struct clk_hw *clk, unsigned long rate,
					unsigned long parent_rate);
void omap3_clk_lock_dpll5(void);

extern struct clk *sdrc_ick_p;
extern struct clk *arm_fck_p;

extern const struct clkops clkops_noncore_dpll_ops;

#endif
