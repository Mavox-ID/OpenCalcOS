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

static int md_table[] = { 1, 2, 3, 4, 6, 8, 12 };

static void master_clk_init(struct clk *clk)
{
	clk->rate *= md_table[__raw_readw(FRQCR) & 0x0007];
}

static struct sh_clk_ops sh7710_master_clk_ops = {
	.init		= master_clk_init,
};

static unsigned long module_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(FRQCR) & 0x0007);
	return clk->parent->rate / md_table[idx];
}

static struct sh_clk_ops sh7710_module_clk_ops = {
	.recalc		= module_clk_recalc,
};

static unsigned long bus_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(FRQCR) & 0x0700) >> 8;
	return clk->parent->rate / md_table[idx];
}

static struct sh_clk_ops sh7710_bus_clk_ops = {
	.recalc		= bus_clk_recalc,
};

static unsigned long cpu_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(FRQCR) & 0x0070) >> 4;
	return clk->parent->rate / md_table[idx];
}

static struct sh_clk_ops sh7710_cpu_clk_ops = {
	.recalc		= cpu_clk_recalc,
};

static struct sh_clk_ops *sh7710_clk_ops[] = {
	&sh7710_master_clk_ops,
	&sh7710_module_clk_ops,
	&sh7710_bus_clk_ops,
	&sh7710_cpu_clk_ops,
};

void __init arch_init_clk_ops(struct sh_clk_ops **ops, int idx)
{
	if (idx < ARRAY_SIZE(sh7710_clk_ops))
		*ops = sh7710_clk_ops[idx];
}

