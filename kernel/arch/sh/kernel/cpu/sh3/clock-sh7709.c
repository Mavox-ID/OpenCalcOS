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
#include <asm/clock.h>
#include <asm/freq.h>
#include <asm/io.h>

static int stc_multipliers[] = { 1, 2, 4, 8, 3, 6, 1, 1 };
static int ifc_divisors[]    = { 1, 2, 4, 1, 3, 1, 1, 1 };
static int pfc_divisors[]    = { 1, 2, 4, 1, 3, 6, 1, 1 };

static void master_clk_init(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x2000) >> 11) | (frqcr & 0x0003);

	clk->rate *= pfc_divisors[idx];
}

static struct sh_clk_ops sh7709_master_clk_ops = {
	.init		= master_clk_init,
};

static unsigned long module_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x2000) >> 11) | (frqcr & 0x0003);

	return clk->parent->rate / pfc_divisors[idx];
}

static struct sh_clk_ops sh7709_module_clk_ops = {
	.recalc		= module_clk_recalc,
};

static unsigned long bus_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = (frqcr & 0x0080) ?
		((frqcr & 0x8000) >> 13) | ((frqcr & 0x0030) >> 4) : 1;

	return clk->parent->rate * stc_multipliers[idx];
}

static struct sh_clk_ops sh7709_bus_clk_ops = {
	.recalc		= bus_clk_recalc,
};

static unsigned long cpu_clk_recalc(struct clk *clk)
{
	int frqcr = __raw_readw(FRQCR);
	int idx = ((frqcr & 0x4000) >> 12) | ((frqcr & 0x000c) >> 2);

	return clk->parent->rate / ifc_divisors[idx];
}

static struct sh_clk_ops sh7709_cpu_clk_ops = {
	.recalc		= cpu_clk_recalc,
};

static struct sh_clk_ops *sh7709_clk_ops[] = {
	&sh7709_master_clk_ops,
	&sh7709_module_clk_ops,
	&sh7709_bus_clk_ops,
	&sh7709_cpu_clk_ops,
};

void __init arch_init_clk_ops(struct sh_clk_ops **ops, int idx)
{
	if (idx < ARRAY_SIZE(sh7709_clk_ops))
		*ops = sh7709_clk_ops[idx];
}
