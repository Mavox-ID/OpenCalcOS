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
#include <asm/io.h>

static int ifc_table[] = { 2, 4, 6, 8, 10, 12, 16, 24 };

/* Clock, Power and Reset Controller */
#define	CPRC_BLOCK_OFF	0x01010000
#define CPRC_BASE	(PHYS_PERIPHERAL_BLOCK + CPRC_BLOCK_OFF)

static unsigned long cprc_base;

static void master_clk_init(struct clk *clk)
{
	int idx = (__raw_readl(cprc_base + 0x00) >> 6) & 0x0007;
	clk->rate *= ifc_table[idx];
}

static struct sh_clk_ops sh5_master_clk_ops = {
	.init		= master_clk_init,
};

static unsigned long module_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(cprc_base) >> 12) & 0x0007;
	return clk->parent->rate / ifc_table[idx];
}

static struct sh_clk_ops sh5_module_clk_ops = {
	.recalc		= module_clk_recalc,
};

static unsigned long bus_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(cprc_base) >> 3) & 0x0007;
	return clk->parent->rate / ifc_table[idx];
}

static struct sh_clk_ops sh5_bus_clk_ops = {
	.recalc		= bus_clk_recalc,
};

static unsigned long cpu_clk_recalc(struct clk *clk)
{
	int idx = (__raw_readw(cprc_base) & 0x0007);
	return clk->parent->rate / ifc_table[idx];
}

static struct sh_clk_ops sh5_cpu_clk_ops = {
	.recalc		= cpu_clk_recalc,
};

static struct sh_clk_ops *sh5_clk_ops[] = {
	&sh5_master_clk_ops,
	&sh5_module_clk_ops,
	&sh5_bus_clk_ops,
	&sh5_cpu_clk_ops,
};

void __init arch_init_clk_ops(struct sh_clk_ops **ops, int idx)
{
	cprc_base = (unsigned long)ioremap_nocache(CPRC_BASE, 1024);
	BUG_ON(!cprc_base);

	if (idx < ARRAY_SIZE(sh5_clk_ops))
		*ops = sh5_clk_ops[idx];
}
