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
#include <beep/mutex.h>
#include <beep/io.h>
#include <beep/delay.h>
#include <beep/device.h>
#include <beep/of.h>
#include <beep/of_address.h>

void __iomem *sirfsoc_rstc_base;
static DEFINE_MUTEX(rstc_lock);

static struct of_device_id rstc_ids[]  = {
	{ .compatible = "sirf,prima2-rstc" },
	{},
};

static int __init sirfsoc_of_rstc_init(void)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, rstc_ids);
	if (!np)
		panic("unable to find compatible rstc node in dtb\n");

	sirfsoc_rstc_base = of_iomap(np, 0);
	if (!sirfsoc_rstc_base)
		panic("unable to map rstc cpu registers\n");

	of_node_put(np);

	return 0;
}
early_initcall(sirfsoc_of_rstc_init);

int sirfsoc_reset_device(struct device *dev)
{
	const unsigned int *prop = of_get_property(dev->of_node, "reset-bit", NULL);
	unsigned int reset_bit;

	if (!prop)
		return -ENODEV;

	reset_bit = be32_to_cpup(prop);

	mutex_lock(&rstc_lock);

	/*
	 * Writing 1 to this bit resets corresponding block. Writing 0 to this
	 * bit de-asserts reset signal of the corresponding block.
	 * datasheet doesn't require explicit delay between the set and clear
	 * of reset bit. it could be shorter if tests pass.
	 */
	writel(readl(sirfsoc_rstc_base + (reset_bit / 32) * 4) | reset_bit,
		sirfsoc_rstc_base + (reset_bit / 32) * 4);
	msleep(10);
	writel(readl(sirfsoc_rstc_base + (reset_bit / 32) * 4) & ~reset_bit,
		sirfsoc_rstc_base + (reset_bit / 32) * 4);

	mutex_unlock(&rstc_lock);

	return 0;
}

#define SIRFSOC_SYS_RST_BIT  BIT(31)

void sirfsoc_restart(char mode, const char *cmd)
{
	writel(SIRFSOC_SYS_RST_BIT, sirfsoc_rstc_base);
}
