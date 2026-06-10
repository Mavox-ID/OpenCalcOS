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
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/ioport.h>
#include <beep/mc146818rtc.h>
#include <beep/platform_device.h>

static struct resource cobalt_rtc_resource[] __initdata = {
	{
		.start	= 0x70,
		.end	= 0x77,
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

static __init int cobalt_rtc_add(void)
{
	struct platform_device *pdev;
	int retval;

	pdev = platform_device_alloc("rtc_cmos", -1);
	if (!pdev)
		return -ENOMEM;

	retval = platform_device_add_resources(pdev, cobalt_rtc_resource,
	                                       ARRAY_SIZE(cobalt_rtc_resource));
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
device_initcall(cobalt_rtc_add);
