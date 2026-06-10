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
#include <beep/dma-mapping.h>
#include <beep/err.h>
#include <beep/irq.h>
#include <beep/slab.h>
#include <beep/platform_device.h>
#include <beep/platform_data/pinctrl-nomadik.h>

#include <mach/hardware.h>
#include <mach/irqs.h>

#include "devices-common.h"

static struct platform_device *
dbx500_add_gpio(struct device *parent, int id, resource_size_t addr, int irq,
		struct nmk_gpio_platform_data *pdata)
{
	struct resource resources[] = {
		{
			.start	= addr,
			.end	= addr + 127,
			.flags	= IORESOURCE_MEM,
		},
		{
			.start	= irq,
			.end	= irq,
			.flags	= IORESOURCE_IRQ,
		}
	};

	return platform_device_register_resndata(
		parent,
		"gpio",
		id,
		resources,
		ARRAY_SIZE(resources),
		pdata,
		sizeof(*pdata));
}

void dbx500_add_gpios(struct device *parent, resource_size_t *base, int num,
		      int irq, struct nmk_gpio_platform_data *pdata)
{
	int first = 0;
	int i;

	for (i = 0; i < num; i++, first += 32, irq++) {
		pdata->first_gpio = first;
		pdata->first_irq = NOMADIK_GPIO_TO_IRQ(first);
		pdata->num_gpio = 32;

		dbx500_add_gpio(parent, i, base[i], irq, pdata);
	}
}
