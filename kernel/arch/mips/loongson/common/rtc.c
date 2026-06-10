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
#include <beep/platform_device.h>
#include <beep/mc146818rtc.h>

struct resource loongson_rtc_resources[] = {
	{
		.start	= RTC_PORT(0),
		.end	= RTC_PORT(1),
		.flags	= IORESOURCE_IO,
	}, {
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	}
};

static struct platform_device loongson_rtc_device = {
	.name		= "rtc_cmos",
	.id		= -1,
	.resource	= loongson_rtc_resources,
	.num_resources	= ARRAY_SIZE(loongson_rtc_resources),
};


static int __init loongson_rtc_platform_init(void)
{
	platform_device_register(&loongson_rtc_device);
	return 0;
}

device_initcall(loongson_rtc_platform_init);
