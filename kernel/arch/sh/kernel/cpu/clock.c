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
#include <beep/clk.h>
#include <asm/clock.h>
#include <asm/machvec.h>

int __init clk_init(void)
{
	int ret;

	ret = arch_clk_init();
	if (unlikely(ret)) {
		pr_err("%s: CPU clock registration failed.\n", __func__);
		return ret;
	}

	if (sh_mv.mv_clk_init) {
		ret = sh_mv.mv_clk_init();
		if (unlikely(ret)) {
			pr_err("%s: machvec clock initialization failed.\n",
			       __func__);
			return ret;
		}
	}

	/* Kick the child clocks.. */
	recalculate_root_clocks();

	/* Enable the necessary init clocks */
	clk_enable_init_clocks();

	return ret;
}


