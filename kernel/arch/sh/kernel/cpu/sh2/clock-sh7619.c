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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/io.h>
#include <asm/clock.h>
#include <asm/freq.h>
#include <asm/processor.h>

static const int pll1rate[] = {1,2};
static const int pfc_divisors[] = {1,2,0,4};
static unsigned int pll2_mult;

static void master_clk_init(struct clk *clk)
{
	clk->rate *= pll2_mult * pll1rate[(__raw_readw(FREQCR) >> 8) & 7];
}

static struct sh_clk_ops sh7619_master_clk_ops = {
	.init		= master_clk_init,
};

static unsigned long module_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(FREQCR) & 0x0007);
	return clk->parent->rate / pfc_divisors[idx];
}

static struct sh_clk_ops sh7619_module_clk_ops = {
	.recalc		= module_clk_recalc,
};

static unsigned long bus_clk_recalc(struct clk *clk)
{
	return clk->parent->rate / pll1rate[(__raw_readw(FREQCR) >> 8) & 7];
}

static struct sh_clk_ops sh7619_bus_clk_ops = {
	.recalc		= bus_clk_recalc,
};

static struct sh_clk_ops sh7619_cpu_clk_ops = {
	.recalc		= followparent_recalc,
};

static struct sh_clk_ops *sh7619_clk_ops[] = {
	&sh7619_master_clk_ops,
	&sh7619_module_clk_ops,
	&sh7619_bus_clk_ops,
	&sh7619_cpu_clk_ops,
};

void __init arch_init_clk_ops(struct sh_clk_ops **ops, int idx)
{
	if (test_mode_pin(MODE_PIN2 | MODE_PIN0) ||
	    test_mode_pin(MODE_PIN2 | MODE_PIN1))
		pll2_mult = 2;
	else if (test_mode_pin(MODE_PIN0) || test_mode_pin(MODE_PIN1))
		pll2_mult = 4;

	BUG_ON(!pll2_mult);

	if (idx < ARRAY_SIZE(sh7619_clk_ops))
		*ops = sh7619_clk_ops[idx];
}
