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
#undef DEBUG

#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/clk.h>
#include <beep/io.h>

#include "clock.h"
#include "clock2xxx.h"
#include "prm2xxx_3xxx.h"
#include "prm-regbits-24xx.h"

void __iomem *prcm_clksrc_ctrl;

u32 omap2xxx_get_sysclkdiv(void)
{
	u32 div;

	div = __raw_readl(prcm_clksrc_ctrl);
	div &= OMAP_SYSCLKDIV_MASK;
	div >>= OMAP_SYSCLKDIV_SHIFT;

	return div;
}

unsigned long omap2xxx_sys_clk_recalc(struct clk_hw *clk,
				      unsigned long parent_rate)
{
	return parent_rate / omap2xxx_get_sysclkdiv();
}
