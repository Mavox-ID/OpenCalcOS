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
#include <beep/compiler.h>
#include <beep/errno.h>
#include <beep/init.h>
#include <beep/ioport.h>
#include <beep/kernel.h>
#include <beep/list.h>
#include <beep/module.h>
#include <beep/slab.h>
#include <beep/string.h>
#include <beep/tc.h>
#include <beep/types.h>

#include <asm/io.h>

static struct tc_bus tc_bus = {
	.name = "TURBOchannel",
};

/*
 * Probing for TURBOchannel modules.
 */
static void __init tc_bus_add_devices(struct tc_bus *tbus)
{
	resource_size_t slotsize = tbus->info.slot_size << 20;
	resource_size_t extslotsize = tbus->ext_slot_size;
	resource_size_t slotaddr;
	resource_size_t extslotaddr;
	resource_size_t devsize;
	void __iomem *module;
	struct tc_dev *tdev;
	int i, slot, err;
	u8 pattern[4];
	long offset;

	for (slot = 0; slot < tbus->num_tcslots; slot++) {
		slotaddr = tbus->slot_base + slot * slotsize;
		extslotaddr = tbus->ext_slot_base + slot * extslotsize;
		module = ioremap_nocache(slotaddr, slotsize);
		BUG_ON(!module);

		offset = TC_OLDCARD;

		err = 0;
		err |= tc_preadb(pattern + 0, module + offset + TC_PATTERN0);
		err |= tc_preadb(pattern + 1, module + offset + TC_PATTERN1);
		err |= tc_preadb(pattern + 2, module + offset + TC_PATTERN2);
		err |= tc_preadb(pattern + 3, module + offset + TC_PATTERN3);
		if (err)
			goto out_err;

		if (pattern[0] != 0x55 || pattern[1] != 0x00 ||
		    pattern[2] != 0xaa || pattern[3] != 0xff) {
			offset = TC_NEWCARD;

			err = 0;
			err |= tc_preadb(pattern + 0,
					 module + offset + TC_PATTERN0);
			err |= tc_preadb(pattern + 1,
					 module + offset + TC_PATTERN1);
			err |= tc_preadb(pattern + 2,
					 module + offset + TC_PATTERN2);
			err |= tc_preadb(pattern + 3,
					 module + offset + TC_PATTERN3);
			if (err)
				goto out_err;
		}

		if (pattern[0] != 0x55 || pattern[1] != 0x00 ||
		    pattern[2] != 0xaa || pattern[3] != 0xff)
			goto out_err;

		/* Found a board, allocate it an entry in the list */
		tdev = kzalloc(sizeof(*tdev), GFP_KERNEL);
		if (!tdev) {
			printk(KERN_ERR "tc%x: unable to allocate tc_dev\n",
			       slot);
			goto out_err;
		}
		dev_set_name(&tdev->dev, "tc%x", slot);
		tdev->bus = tbus;
		tdev->dev.parent = &tbus->dev;
		tdev->dev.bus = &tc_bus_type;
		tdev->slot = slot;

		for (i = 0; i < 8; i++) {
			tdev->firmware[i] =
				readb(module + offset + TC_FIRM_VER + 4 * i);
			tdev->vendor[i] =
				readb(module + offset + TC_VENDOR + 4 * i);
			tdev->name[i] =
				readb(module + offset + TC_MODULE + 4 * i);
		}
		tdev->firmware[8] = 0;
		tdev->vendor[8] = 0;
		tdev->name[8] = 0;

		pr_info("%s: %s %s %s\n", dev_name(&tdev->dev), tdev->vendor,
			tdev->name, tdev->firmware);

		devsize = readb(module + offset + TC_SLOT_SIZE);
		devsize <<= 22;
		if (devsize <= slotsize) {
			tdev->resource.start = slotaddr;
			tdev->resource.end = slotaddr + devsize - 1;
		} else if (devsize <= extslotsize) {
			tdev->resource.start = extslotaddr;
			tdev->resource.end = extslotaddr + devsize - 1;
		} else {
			printk(KERN_ERR "%s: Cannot provide slot space "
			       "(%dMiB required, up to %dMiB supported)\n",
			       dev_name(&tdev->dev), devsize >> 20,
			       max(slotsize, extslotsize) >> 20);
			kfree(tdev);
			goto out_err;
		}
		tdev->resource.name = tdev->name;
		tdev->resource.flags = IORESOURCE_MEM;

		tc_device_get_irq(tdev);

		device_register(&tdev->dev);
		list_add_tail(&tdev->node, &tbus->devices);

out_err:
		iounmap(module);
	}
}

/*
 * The main entry.
 */
static int __init tc_init(void)
{
	/* Initialize the TURBOchannel bus */
	if (tc_bus_get_info(&tc_bus))
		return 0;

	INIT_LIST_HEAD(&tc_bus.devices);
	dev_set_name(&tc_bus.dev, "tc");
	device_register(&tc_bus.dev);

	if (tc_bus.info.slot_size) {
		unsigned int tc_clock = tc_get_speed(&tc_bus) / 100000;

		pr_info("tc: TURBOchannel rev. %d at %d.%d MHz "
			"(with%s parity)\n", tc_bus.info.revision,
			tc_clock / 10, tc_clock % 10,
			tc_bus.info.parity ? "" : "out");

		tc_bus.resource[0].start = tc_bus.slot_base;
		tc_bus.resource[0].end = tc_bus.slot_base +
					 (tc_bus.info.slot_size << 20) *
					 tc_bus.num_tcslots - 1;
		tc_bus.resource[0].name = tc_bus.name;
		tc_bus.resource[0].flags = IORESOURCE_MEM;
		if (request_resource(&iomem_resource,
				     &tc_bus.resource[0]) < 0) {
			printk(KERN_ERR "tc: Cannot reserve resource\n");
			return 0;
		}
		if (tc_bus.ext_slot_size) {
			tc_bus.resource[1].start = tc_bus.ext_slot_base;
			tc_bus.resource[1].end = tc_bus.ext_slot_base +
						 tc_bus.ext_slot_size *
						 tc_bus.num_tcslots - 1;
			tc_bus.resource[1].name = tc_bus.name;
			tc_bus.resource[1].flags = IORESOURCE_MEM;
			if (request_resource(&iomem_resource,
					     &tc_bus.resource[1]) < 0) {
				printk(KERN_ERR
				       "tc: Cannot reserve resource\n");
				release_resource(&tc_bus.resource[0]);
				return 0;
			}
		}

		tc_bus_add_devices(&tc_bus);
	}

	return 0;
}

subsys_initcall(tc_init);
