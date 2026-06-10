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
#include <beep/time.h>
#include <beep/err.h>
#include <beep/clk.h>

#include <asm/time.h>
#include <asm/mach-ar7/ar7.h>

void __init plat_time_init(void)
{
	struct clk *cpu_clk;

	/* Initialize ar7 clocks so the CPU clock frequency is correct */
	ar7_init_clocks();

	cpu_clk = clk_get(NULL, "cpu");
	if (IS_ERR(cpu_clk)) {
		printk(KERN_ERR "unable to get cpu clock\n");
		return;
	}

	mips_hpt_frequency = clk_get_rate(cpu_clk) / 2;
}
