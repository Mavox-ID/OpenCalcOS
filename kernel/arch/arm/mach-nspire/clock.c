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
#include <asm-generic/errno.h>

#include <mach/clkdev.h>

void clk_disable(struct clk *clk)
{
}

int clk_enable(struct clk *clk)
{
	return 0;
}

unsigned long clk_get_rate(struct clk *clk)
{
	if (clk->get_rate)
		clk->get_rate(clk);

	return clk->rate;
}

int clk_set_rate(struct clk *clk, unsigned long rate)
{
	if (clk->set_rate)
		return clk->set_rate(clk, rate);

	return -ENOSYS;
}
