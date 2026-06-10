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
#include <beep/io.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/platform_device.h>
#include <mach/highlander.h>
#include <asm/push-switch.h>

static irqreturn_t psw_irq_handler(int irq, void *arg)
{
	struct platform_device *pdev = arg;
	struct push_switch *psw = platform_get_drvdata(pdev);
	struct push_switch_platform_info *psw_info = pdev->dev.platform_data;
	unsigned int l, mask;
	int ret = 0;

	l = __raw_readw(PA_DBSW);

	/* Nothing to do if there's no state change */
	if (psw->state) {
		ret = 1;
		goto out;
	}

	mask = l & 0x70;
	/* Figure out who raised it */
	if (mask & (1 << psw_info->bit)) {
		psw->state = !!(mask & (1 << psw_info->bit));
		if (psw->state)	/* debounce */
			mod_timer(&psw->debounce, jiffies + 50);

		ret = 1;
	}

out:
	/* Clear the switch IRQs */
	l |= (0x7 << 12);
	__raw_writew(l, PA_DBSW);

	return IRQ_RETVAL(ret);
}

static struct resource psw_resources[] = {
	[0] = {
		.start	= IRQ_PSW,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct push_switch_platform_info s2_platform_data = {
	.name		= "s2",
	.bit		= 6,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
};

static struct platform_device s2_switch_device = {
	.name		= "push-switch",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= {
		.platform_data = &s2_platform_data,
	},
};

static struct push_switch_platform_info s3_platform_data = {
	.name		= "s3",
	.bit		= 5,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
};

static struct platform_device s3_switch_device = {
	.name		= "push-switch",
	.id		= 1,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= {
		.platform_data = &s3_platform_data,
	},
};

static struct push_switch_platform_info s4_platform_data = {
	.name		= "s4",
	.bit		= 4,
	.irq_flags	= IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
			  IRQF_SHARED,
	.irq_handler	= psw_irq_handler,
};

static struct platform_device s4_switch_device = {
	.name		= "push-switch",
	.id		= 2,
	.num_resources	= ARRAY_SIZE(psw_resources),
	.resource	= psw_resources,
	.dev		= {
		.platform_data = &s4_platform_data,
	},
};

static struct platform_device *psw_devices[] = {
	&s2_switch_device, &s3_switch_device, &s4_switch_device,
};

static int __init psw_init(void)
{
	return platform_add_devices(psw_devices, ARRAY_SIZE(psw_devices));
}
module_init(psw_init);
