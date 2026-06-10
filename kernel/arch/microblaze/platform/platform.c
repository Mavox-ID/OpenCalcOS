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
#include <beep/of_platform.h>
#include <asm/prom.h>
#include <asm/setup.h>

static struct of_device_id xilinx_of_bus_ids[] __initdata = {
	{ .compatible = "simple-bus", },
	{ .compatible = "xlnx,compound", },
	{}
};

static int __init microblaze_device_probe(void)
{
	of_platform_bus_probe(NULL, xilinx_of_bus_ids, NULL);
	of_platform_reset_gpio_probe();
	return 0;
}
device_initcall(microblaze_device_probe);
