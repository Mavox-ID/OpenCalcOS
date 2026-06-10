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
#include <beep/export.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/reboot.h>
#include <beep/of_device.h>

#include <asm/prom.h>
#include <asm/io.h>

static void __iomem *power_reg;

static irqreturn_t power_handler(int irq, void *dev_id)
{
	orderly_poweroff(true);

	/* FIXME: Check registers for status... */
	return IRQ_HANDLED;
}

static int has_button_interrupt(unsigned int irq, struct device_node *dp)
{
	if (irq == 0xffffffff)
		return 0;
	if (!of_find_property(dp, "button", NULL))
		return 0;

	return 1;
}

static int power_probe(struct platform_device *op)
{
	struct resource *res = &op->resource[0];
	unsigned int irq = op->archdata.irqs[0];

	power_reg = of_ioremap(res, 0, 0x4, "power");

	printk(KERN_INFO "%s: Control reg at %llx\n",
	       op->dev.of_node->name, res->start);

	if (has_button_interrupt(irq, op->dev.of_node)) {
		if (request_irq(irq,
				power_handler, 0, "power", NULL) < 0)
			printk(KERN_ERR "power: Cannot setup IRQ handler.\n");
	}

	return 0;
}

static const struct of_device_id power_match[] = {
	{
		.name = "power",
	},
	{},
};

static struct platform_driver power_driver = {
	.probe		= power_probe,
	.driver = {
		.name = "power",
		.owner = THIS_MODULE,
		.of_match_table = power_match,
	},
};

static int __init power_init(void)
{
	return platform_driver_register(&power_driver);
}

device_initcall(power_init);
