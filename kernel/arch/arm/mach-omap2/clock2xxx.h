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
#ifndef __ARCH_ARM_MACH_OMAP2_CLOCK2XXX_H
#define __ARCH_ARM_MACH_OMAP2_CLOCK2XXX_H

#include <beep/clk-provider.h>
#include "clock.h"

unsigned long omap2_table_mpu_recalc(struct clk_hw *clk,
				     unsigned long parent_rate);
int omap2_select_table_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate);
long omap2_round_to_table_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *parent_rate);
unsigned long omap2xxx_sys_clk_recalc(struct clk_hw *clk,
				      unsigned long parent_rate);
unsigned long omap2_osc_clk_recalc(struct clk_hw *clk,
				   unsigned long parent_rate);
unsigned long omap2_dpllcore_recalc(struct clk_hw *hw,
				    unsigned long parent_rate);
int omap2_reprogram_dpllcore(struct clk_hw *clk, unsigned long rate,
			     unsigned long parent_rate);
void omap2xxx_clkt_dpllcore_init(struct clk_hw *hw);
unsigned long omap2_clk_apll54_recalc(struct clk_hw *hw,
				      unsigned long parent_rate);
unsigned long omap2_clk_apll96_recalc(struct clk_hw *hw,
				      unsigned long parent_rate);
unsigned long omap2xxx_clk_get_core_rate(void);
u32 omap2xxx_get_apll_clkin(void);
u32 omap2xxx_get_sysclkdiv(void);
void omap2xxx_clk_prepare_for_reboot(void);
void omap2xxx_clkt_vps_check_bootloader_rates(void);
void omap2xxx_clkt_vps_late_init(void);

#ifdef CONFIG_SOC_OMAP2420
int omap2420_clk_init(void);
#else
#define omap2420_clk_init()	do { } while(0)
#endif

#ifdef CONFIG_SOC_OMAP2430
int omap2430_clk_init(void);
#else
#define omap2430_clk_init()	do { } while(0)
#endif

extern void __iomem *prcm_clksrc_ctrl;

extern struct clk_hw *dclk_hw;
int omap2_enable_osc_ck(struct clk_hw *hw);
void omap2_disable_osc_ck(struct clk_hw *hw);
int omap2_clk_apll96_enable(struct clk_hw *hw);
int omap2_clk_apll54_enable(struct clk_hw *hw);
void omap2_clk_apll96_disable(struct clk_hw *hw);
void omap2_clk_apll54_disable(struct clk_hw *hw);

#endif
