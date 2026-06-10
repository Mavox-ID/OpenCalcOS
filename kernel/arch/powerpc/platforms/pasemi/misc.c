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
#include <beep/errno.h>
#include <beep/kernel.h>
#include <beep/pci.h>
#include <beep/of.h>
#include <beep/i2c.h>

#ifdef CONFIG_I2C_BOARDINFO
/* The below is from fsl_soc.c.  It's copied because since there are no
 * official bus bindings at this time it doesn't make sense to share across
 * the platforms, even though they happen to be common.
 */
struct i2c_driver_device {
	char    *of_device;
	char    *i2c_type;
};

static struct i2c_driver_device i2c_devices[] __initdata = {
	{"dallas,ds1338",  "ds1338"},
};

static int __init find_i2c_driver(struct device_node *node,
				     struct i2c_board_info *info)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(i2c_devices); i++) {
		if (!of_device_is_compatible(node, i2c_devices[i].of_device))
			continue;
		if (strlcpy(info->type, i2c_devices[i].i2c_type,
			    I2C_NAME_SIZE) >= I2C_NAME_SIZE)
			return -ENOMEM;
		return 0;
	}
	return -ENODEV;
}

static int __init pasemi_register_i2c_devices(void)
{
	struct pci_dev *pdev;
	struct device_node *adap_node;
	struct device_node *node;

	pdev = NULL;
	while ((pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa003, pdev))) {
		adap_node = pci_device_to_OF_node(pdev);

		if (!adap_node)
			continue;

		node = NULL;
		while ((node = of_get_next_child(adap_node, node))) {
			struct i2c_board_info info = {};
			const u32 *addr;
			int len;

			addr = of_get_property(node, "reg", &len);
			if (!addr || len < sizeof(int) ||
			    *addr > (1 << 10) - 1) {
				printk(KERN_WARNING
					"pasemi_register_i2c_devices: "
					"invalid i2c device entry\n");
				continue;
			}

			info.irq = irq_of_parse_and_map(node, 0);
			if (info.irq == NO_IRQ)
				info.irq = -1;

			if (find_i2c_driver(node, &info) < 0)
				continue;

			info.addr = *addr;

			i2c_register_board_info(PCI_FUNC(pdev->devfn), &info,
						1);
		}
	}
	return 0;
}
device_initcall(pasemi_register_i2c_devices);
#endif
