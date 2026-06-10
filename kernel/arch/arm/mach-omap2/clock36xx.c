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
#include <beep/clk.h>
#include <beep/io.h>

#include "clock.h"
#include "clock36xx.h"


/**
 * omap36xx_pwrdn_clk_enable_with_hsdiv_restore - enable clocks suffering
 *         from HSDivider PWRDN problem Implements Errata ID: i556.
 * @clk: DPLL output struct clk
 *
 * 3630 only: dpll3_m3_ck, dpll4_m2_ck, dpll4_m3_ck, dpll4_m4_ck,
 * dpll4_m5_ck & dpll4_m6_ck dividers gets loaded with reset
 * valueafter their respective PWRDN bits are set.  Any dummy write
 * (Any other value different from the Read value) to the
 * corresponding CM_CLKSEL register will refresh the dividers.
 */
int omap36xx_pwrdn_clk_enable_with_hsdiv_restore(struct clk_hw *clk)
{
	struct clk_hw_omap *parent;
	struct clk_hw *parent_hw;
	u32 dummy_v, orig_v, clksel_shift;
	int ret;

	/* Clear PWRDN bit of HSDIVIDER */
	ret = omap2_dflt_clk_enable(clk);

	parent_hw = __clk_get_hw(__clk_get_parent(clk->clk));
	parent = to_clk_hw_omap(parent_hw);

	/* Restore the dividers */
	if (!ret) {
		clksel_shift = __ffs(parent->clksel_mask);
		orig_v = __raw_readl(parent->clksel_reg);
		dummy_v = orig_v;

		/* Write any other value different from the Read value */
		dummy_v ^= (1 << clksel_shift);
		__raw_writel(dummy_v, parent->clksel_reg);

		/* Write the original divider */
		__raw_writel(orig_v, parent->clksel_reg);
	}

	return ret;
}
