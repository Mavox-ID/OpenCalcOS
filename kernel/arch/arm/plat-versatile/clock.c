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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/clk.h>
#include <beep/mutex.h>

#include <asm/hardware/icst.h>

#include <mach/clkdev.h>

int clk_enable(struct clk *clk)
{
	return 0;
}
EXPORT_SYMBOL(clk_enable);

void clk_disable(struct clk *clk)
{
}
EXPORT_SYMBOL(clk_disable);

unsigned long clk_get_rate(struct clk *clk)
{
	return clk->rate;
}
EXPORT_SYMBOL(clk_get_rate);

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	long ret = -EIO;
	if (clk->ops && clk->ops->round)
		ret = clk->ops->round(clk, rate);
	return ret;
}
EXPORT_SYMBOL(clk_round_rate);

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	int ret = -EIO;
	if (clk->ops && clk->ops->set)
		ret = clk->ops->set(clk, rate);
	return ret;
}
EXPORT_SYMBOL(clk_set_rate);

long icst_clk_round(struct clk *clk, unsigned long rate)
{
	struct icst_vco vco;
	vco = icst_hz_to_vco(clk->params, rate);
	return icst_hz(clk->params, vco);
}
EXPORT_SYMBOL(icst_clk_round);

int icst_clk_set(struct clk *clk, unsigned long rate)
{
	struct icst_vco vco;

	vco = icst_hz_to_vco(clk->params, rate);
	clk->rate = icst_hz(clk->params, vco);
	clk->ops->setvco(clk, vco);

	return 0;
}
EXPORT_SYMBOL(icst_clk_set);
