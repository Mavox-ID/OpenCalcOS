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
#include "../hardware.h"
#include "devices-common.h"

#define imx_mxc_rtc_data_entry_single(soc, _devid)			\
	{								\
		.devid = _devid,					\
		.iobase = soc ## _RTC_BASE_ADDR,			\
		.irq = soc ## _INT_RTC,					\
	}

#ifdef CONFIG_SOC_IMX31
const struct imx_mxc_rtc_data imx31_mxc_rtc_data __initconst =
	imx_mxc_rtc_data_entry_single(MX31, "imx21-rtc");
#endif /* ifdef CONFIG_SOC_IMX31 */

#ifdef CONFIG_SOC_IMX35
const struct imx_mxc_rtc_data imx35_mxc_rtc_data __initconst =
	imx_mxc_rtc_data_entry_single(MX35, "imx21-rtc");
#endif /* ifdef CONFIG_SOC_IMX35 */

struct platform_device *__init imx_add_mxc_rtc(
		const struct imx_mxc_rtc_data *data)
{
	struct resource res[] = {
		{
			.start = data->iobase,
			.end = data->iobase + SZ_16K - 1,
			.flags = IORESOURCE_MEM,
		}, {
			.start = data->irq,
			.end = data->irq,
			.flags = IORESOURCE_IRQ,
		},
	};

	return imx_add_platform_device(data->devid, -1,
			res, ARRAY_SIZE(res), NULL, 0);
}
