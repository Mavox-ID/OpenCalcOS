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
#include <beep/platform_device.h>

static struct resource __initdata sead3_lcd_resource = {
		.start	= 0x1f000400,
		.end	= 0x1f00041f,
		.flags	= IORESOURCE_MEM,
};

static __init int sead3_lcd_add(void)
{
	struct platform_device *pdev;
	int retval;

	/* SEAD-3 and Cobalt platforms use same display type. */
	pdev = platform_device_alloc("cobalt-lcd", -1);
	if (!pdev)
		return -ENOMEM;

	retval = platform_device_add_resources(pdev, &sead3_lcd_resource, 1);
	if (retval)
		goto err_free_device;

	retval = platform_device_add(pdev);
	if (retval)
		goto err_free_device;

	return 0;

err_free_device:
	platform_device_put(pdev);

	return retval;
}

device_initcall(sead3_lcd_add);
