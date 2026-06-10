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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/sh_clk.h>
#include <beep/export.h>

int __init shmobile_clk_init(void)
{
	/* Kick the child clocks.. */
	recalculate_root_clocks();

	/* Enable the necessary init clocks */
	clk_enable_init_clocks();

	return 0;
}

int __clk_get(struct clk *clk)
{
	return 1;
}
EXPORT_SYMBOL(__clk_get);

void __clk_put(struct clk *clk)
{
}
EXPORT_SYMBOL(__clk_put);
