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
#include <beep/dma-mapping.h>

#include "../hardware.h"
#include "devices-common.h"

#define imx_fsl_usb2_udc_data_entry_single(soc, _devid)			\
	{								\
		.devid = _devid,					\
		.iobase = soc ## _USB_OTG_BASE_ADDR,			\
		.irq = soc ## _INT_USB_OTG,				\
	}

#ifdef CONFIG_SOC_IMX25
const struct imx_fsl_usb2_udc_data imx25_fsl_usb2_udc_data __initconst =
	imx_fsl_usb2_udc_data_entry_single(MX25, "imx-udc-mx27");
#endif /* ifdef CONFIG_SOC_IMX25 */

#ifdef CONFIG_SOC_IMX27
const struct imx_fsl_usb2_udc_data imx27_fsl_usb2_udc_data __initconst =
	imx_fsl_usb2_udc_data_entry_single(MX27, "imx-udc-mx27");
#endif /* ifdef CONFIG_SOC_IMX27 */

#ifdef CONFIG_SOC_IMX31
const struct imx_fsl_usb2_udc_data imx31_fsl_usb2_udc_data __initconst =
	imx_fsl_usb2_udc_data_entry_single(MX31, "imx-udc-mx27");
#endif /* ifdef CONFIG_SOC_IMX31 */

#ifdef CONFIG_SOC_IMX35
const struct imx_fsl_usb2_udc_data imx35_fsl_usb2_udc_data __initconst =
	imx_fsl_usb2_udc_data_entry_single(MX35, "imx-udc-mx27");
#endif /* ifdef CONFIG_SOC_IMX35 */

#ifdef CONFIG_SOC_IMX51
const struct imx_fsl_usb2_udc_data imx51_fsl_usb2_udc_data __initconst =
	imx_fsl_usb2_udc_data_entry_single(MX51, "imx-udc-mx51");
#endif

struct platform_device *__init imx_add_fsl_usb2_udc(
		const struct imx_fsl_usb2_udc_data *data,
		const struct fsl_usb2_platform_data *pdata)
{
	struct resource res[] = {
		{
			.start = data->iobase,
			.end = data->iobase + SZ_512 - 1,
			.flags = IORESOURCE_MEM,
		}, {
			.start = data->irq,
			.end = data->irq,
			.flags = IORESOURCE_IRQ,
		},
	};
	return imx_add_platform_device_dmamask(data->devid, -1,
			res, ARRAY_SIZE(res),
			pdata, sizeof(*pdata), DMA_BIT_MASK(32));
}
