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
#include "devices-common.h"

struct platform_device __init __maybe_unused *imx_add_imx_dma(char *name,
	resource_size_t iobase, int irq, int irq_err)
{
	struct resource res[] = {
		{
			.start = iobase,
			.end = iobase + SZ_4K - 1,
			.flags = IORESOURCE_MEM,
		}, {
			.start = irq,
			.end = irq,
			.flags = IORESOURCE_IRQ,
		}, {
			.start = irq_err,
			.end = irq_err,
			.flags = IORESOURCE_IRQ,
		},
	};

	return platform_device_register_resndata(&mxc_ahb_bus,
			name, -1, res, ARRAY_SIZE(res), NULL, 0);
}

struct platform_device __init __maybe_unused *imx_add_imx_sdma(char *name,
	resource_size_t iobase, int irq, struct sdma_platform_data *pdata)
{
	struct resource res[] = {
		{
			.start = iobase,
			.end = iobase + SZ_16K - 1,
			.flags = IORESOURCE_MEM,
		}, {
			.start = irq,
			.end = irq,
			.flags = IORESOURCE_IRQ,
		},
	};

	return platform_device_register_resndata(&mxc_ahb_bus, name,
			-1, res, ARRAY_SIZE(res), pdata, sizeof(*pdata));
}
