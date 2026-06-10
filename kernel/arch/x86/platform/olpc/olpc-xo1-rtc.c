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
#include <beep/mc146818rtc.h>
#include <beep/platform_device.h>
#include <beep/rtc.h>
#include <beep/of.h>

#include <asm/msr.h>
#include <asm/olpc.h>

static void rtc_wake_on(struct device *dev)
{
	olpc_xo1_pm_wakeup_set(CS5536_PM_RTC);
}

static void rtc_wake_off(struct device *dev)
{
	olpc_xo1_pm_wakeup_clear(CS5536_PM_RTC);
}

static struct resource rtc_platform_resource[] = {
	[0] = {
		.start	= RTC_PORT(0),
		.end	= RTC_PORT(1),
		.flags	= IORESOURCE_IO,
	},
	[1] = {
		.start	= RTC_IRQ,
		.end	= RTC_IRQ,
		.flags	= IORESOURCE_IRQ,
	}
};

static struct cmos_rtc_board_info rtc_info = {
	.rtc_day_alarm = 0,
	.rtc_mon_alarm = 0,
	.rtc_century = 0,
	.wake_on = rtc_wake_on,
	.wake_off = rtc_wake_off,
};

static struct platform_device xo1_rtc_device = {
	.name = "rtc_cmos",
	.id = -1,
	.num_resources = ARRAY_SIZE(rtc_platform_resource),
	.dev.platform_data = &rtc_info,
	.resource = rtc_platform_resource,
};

static int __init xo1_rtc_init(void)
{
	int r;
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "olpc,xo1-rtc");
	if (!node)
		return 0;
	of_node_put(node);

	pr_info("olpc-xo1-rtc: Initializing OLPC XO-1 RTC\n");
	rdmsrl(MSR_RTC_DOMA_OFFSET, rtc_info.rtc_day_alarm);
	rdmsrl(MSR_RTC_MONA_OFFSET, rtc_info.rtc_mon_alarm);
	rdmsrl(MSR_RTC_CEN_OFFSET, rtc_info.rtc_century);

	r = platform_device_register(&xo1_rtc_device);
	if (r)
		return r;

	device_init_wakeup(&xo1_rtc_device.dev, 1);
	return 0;
}
arch_initcall(xo1_rtc_init);
