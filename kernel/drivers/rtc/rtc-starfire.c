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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/rtc.h>
#include <beep/platform_device.h>

#include <asm/oplib.h>

MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_DESCRIPTION("Starfire RTC driver");
MODULE_LICENSE("GPL");

static u32 starfire_get_time(void)
{
	static char obp_gettod[32];
	static u32 unix_tod;

	sprintf(obp_gettod, "h# %08x unix-gettod",
		(unsigned int) (long) &unix_tod);
	prom_feval(obp_gettod);

	return unix_tod;
}

static int starfire_read_time(struct device *dev, struct rtc_time *tm)
{
	rtc_time_to_tm(starfire_get_time(), tm);
	return rtc_valid_tm(tm);
}

static const struct rtc_class_ops starfire_rtc_ops = {
	.read_time	= starfire_read_time,
};

static int __init starfire_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtc = rtc_device_register("starfire", &pdev->dev,
				     &starfire_rtc_ops, THIS_MODULE);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	platform_set_drvdata(pdev, rtc);

	return 0;
}

static int __exit starfire_rtc_remove(struct platform_device *pdev)
{
	struct rtc_device *rtc = platform_get_drvdata(pdev);

	rtc_device_unregister(rtc);

	return 0;
}

static struct platform_driver starfire_rtc_driver = {
	.driver		= {
		.name	= "rtc-starfire",
		.owner	= THIS_MODULE,
	},
	.remove		= __exit_p(starfire_rtc_remove),
};

static int __init starfire_rtc_init(void)
{
	return platform_driver_probe(&starfire_rtc_driver, starfire_rtc_probe);
}

static void __exit starfire_rtc_exit(void)
{
	platform_driver_unregister(&starfire_rtc_driver);
}

module_init(starfire_rtc_init);
module_exit(starfire_rtc_exit);
