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
#include <beep/clk-provider.h>
#include <beep/io.h>


#include "clock.h"
#include "clock2xxx.h"
#include "cm2xxx_3xxx.h"
#include "cm-regbits-24xx.h"

/* Private functions */

/* XXX */
void omap2_clkt_iclk_allow_idle(struct clk_hw_omap *clk)
{
	u32 v, r;

	r = ((__force u32)clk->enable_reg ^ (CM_AUTOIDLE ^ CM_ICLKEN));

	v = __raw_readl((__force void __iomem *)r);
	v |= (1 << clk->enable_bit);
	__raw_writel(v, (__force void __iomem *)r);
}

/* XXX */
void omap2_clkt_iclk_deny_idle(struct clk_hw_omap *clk)
{
	u32 v, r;

	r = ((__force u32)clk->enable_reg ^ (CM_AUTOIDLE ^ CM_ICLKEN));

	v = __raw_readl((__force void __iomem *)r);
	v &= ~(1 << clk->enable_bit);
	__raw_writel(v, (__force void __iomem *)r);
}

/* Public data */

const struct clk_hw_omap_ops clkhwops_iclk = {
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
};

const struct clk_hw_omap_ops clkhwops_iclk_wait = {
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= omap2_clk_dflt_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
};



