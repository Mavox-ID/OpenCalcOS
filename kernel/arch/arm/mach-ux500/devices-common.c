/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> for ST-Ericsson
 * License terms: GNU General Public License (GPL), version 2.
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
