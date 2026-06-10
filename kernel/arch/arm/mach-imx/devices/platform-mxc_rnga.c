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

struct imx_mxc_rnga_data {
	resource_size_t iobase;
};

#define imx_mxc_rnga_data_entry_single(soc)				\
	{								\
		.iobase = soc ## _RNGA_BASE_ADDR,			\
	}

#ifdef CONFIG_SOC_IMX31
static const struct imx_mxc_rnga_data imx31_mxc_rnga_data __initconst =
	imx_mxc_rnga_data_entry_single(MX31);
#endif /* ifdef CONFIG_SOC_IMX31 */

static struct platform_device *__init imx_add_mxc_rnga(
		const struct imx_mxc_rnga_data *data)
{
	struct resource res[] = {
		{
			.start = data->iobase,
			.end = data->iobase + SZ_16K - 1,
			.flags = IORESOURCE_MEM,
		},
	};
	return imx_add_platform_device("mxc_rnga", -1,
			res, ARRAY_SIZE(res), NULL, 0);
}

static int __init imxXX_add_mxc_rnga(void)
{
	struct platform_device *ret;

#if defined(CONFIG_SOC_IMX31)
	if (cpu_is_mx31())
		ret = imx_add_mxc_rnga(&imx31_mxc_rnga_data);
	else
#endif /* if defined(CONFIG_SOC_IMX31) */
		ret = ERR_PTR(-ENODEV);

	if (IS_ERR(ret))
		return PTR_ERR(ret);

	return 0;
}
arch_initcall(imxXX_add_mxc_rnga);
