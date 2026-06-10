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
#include <beep/of.h>
#include <asm/hardware/cache-l2x0.h>

static struct of_device_id prima2_l2x0_ids[]  = {
	{ .compatible = "sirf,prima2-pl310-cache" },
	{},
};

static int __init sirfsoc_l2x0_init(void)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, prima2_l2x0_ids);
	if (np) {
		pr_info("Initializing prima2 L2 cache\n");
		return l2x0_of_init(0x40000, 0);
	}

	return 0;
}
early_initcall(sirfsoc_l2x0_init);
