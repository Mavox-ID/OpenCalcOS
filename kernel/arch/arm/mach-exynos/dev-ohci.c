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
#include <beep/platform_device.h>
#include <beep/platform_data/usb-exynos.h>

#include <mach/irqs.h>
#include <mach/map.h>

#include <plat/devs.h>
#include <plat/usb-phy.h>

static struct resource exynos4_ohci_resource[] = {
	[0] = DEFINE_RES_MEM(EXYNOS4_PA_OHCI, SZ_256),
	[1] = DEFINE_RES_IRQ(IRQ_USB_HOST),
};

static u64 exynos4_ohci_dma_mask = DMA_BIT_MASK(32);

struct platform_device exynos4_device_ohci = {
	.name		= "exynos-ohci",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(exynos4_ohci_resource),
	.resource	= exynos4_ohci_resource,
	.dev		= {
		.dma_mask		= &exynos4_ohci_dma_mask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	}
};

void __init exynos4_ohci_set_platdata(struct exynos4_ohci_platdata *pd)
{
	struct exynos4_ohci_platdata *npd;

	npd = s3c_set_platdata(pd, sizeof(struct exynos4_ohci_platdata),
			&exynos4_device_ohci);

	if (!npd->phy_init)
		npd->phy_init = s5p_usb_phy_init;
	if (!npd->phy_exit)
		npd->phy_exit = s5p_usb_phy_exit;
}
