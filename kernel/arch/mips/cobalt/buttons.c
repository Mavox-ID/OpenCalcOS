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
#include <beep/platform_device.h>
#include <beep/errno.h>
#include <beep/init.h>

static struct resource cobalt_buttons_resource __initdata = {
	.start	= 0x1d000000,
	.end	= 0x1d000003,
	.flags	= IORESOURCE_MEM,
};

static __init int cobalt_add_buttons(void)
{
	struct platform_device *pd;
	int error;

	pd = platform_device_alloc("Cobalt buttons", -1);
	if (!pd)
		return -ENOMEM;

	error = platform_device_add_resources(pd, &cobalt_buttons_resource, 1);
	if (error)
		goto err_free_device;

	error = platform_device_add(pd);
	if (error)
		goto err_free_device;

	return 0;

 err_free_device:
	platform_device_put(pd);
	return error;
}
device_initcall(cobalt_add_buttons);
