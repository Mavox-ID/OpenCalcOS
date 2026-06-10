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
#include <beep/clk.h>
#include <beep/err.h>
#include <asm/time.h>
#include <platform.h>

void __init plat_time_init(void)
{
	struct clk *clk;

	/* Initialize LS1X clocks */
	ls1x_clk_init();

	/* setup mips r4k timer */
	clk = clk_get(NULL, "cpu");
	if (IS_ERR(clk))
		panic("unable to get cpu clock, err=%ld", PTR_ERR(clk));

	mips_hpt_frequency = clk_get_rate(clk) / 2;
}
