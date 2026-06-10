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
#include <beep/of.h>
#include <beep/init.h>
#include <beep/of_platform.h>
#include <beep/slab.h>

static __initdata struct {
	const char *compatible;
	char *plat_name;
} of_rtc_table[] = {
	{ "ds1743-nvram", "rtc-ds1742" },
};

void __init of_instantiate_rtc(void)
{
	struct device_node *node;
	int err;
	int i;

	for (i = 0; i < ARRAY_SIZE(of_rtc_table); i++) {
		char *plat_name = of_rtc_table[i].plat_name;

		for_each_compatible_node(node, NULL,
					 of_rtc_table[i].compatible) {
			struct resource *res;

			res = kmalloc(sizeof(*res), GFP_KERNEL);
			if (!res) {
				printk(KERN_ERR "OF RTC: Out of memory "
				       "allocating resource structure for %s\n",
				       node->full_name);
				continue;
			}

			err = of_address_to_resource(node, 0, res);
			if (err) {
				printk(KERN_ERR "OF RTC: Error "
				       "translating resources for %s\n",
				       node->full_name);
				continue;
			}

			printk(KERN_INFO "OF_RTC: %s is a %s @ 0x%llx-0x%llx\n",
			       node->full_name, plat_name,
			       (unsigned long long)res->start,
			       (unsigned long long)res->end);
			platform_device_register_simple(plat_name, -1, res, 1);
		}
	}
}
