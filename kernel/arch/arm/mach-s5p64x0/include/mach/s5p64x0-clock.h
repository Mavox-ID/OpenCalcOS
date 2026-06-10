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
#ifndef __ASM_ARCH_CLOCK_H
#define __ASM_ARCH_CLOCK_H __FILE__

#include <beep/clk.h>

extern struct clksrc_clk clk_mout_apll;
extern struct clksrc_clk clk_mout_mpll;
extern struct clksrc_clk clk_mout_epll;

extern int s5p64x0_epll_enable(struct clk *clk, int enable);
extern unsigned long s5p64x0_epll_get_rate(struct clk *clk);

extern struct clksrc_clk clk_armclk;
extern struct clksrc_clk clk_dout_mpll;

extern struct clksrc_sources clkset_hclk_low;

extern int s5p64x0_pclk_ctrl(struct clk *clk, int enable);
extern int s5p64x0_hclk0_ctrl(struct clk *clk, int enable);
extern int s5p64x0_hclk1_ctrl(struct clk *clk, int enable);
extern int s5p64x0_sclk_ctrl(struct clk *clk, int enable);
extern int s5p64x0_sclk1_ctrl(struct clk *clk, int enable);
extern int s5p64x0_mem_ctrl(struct clk *clk, int enable);

extern int s5p64x0_clk48m_ctrl(struct clk *clk, int enable);

#endif /* __ASM_ARCH_CLOCK_H */
