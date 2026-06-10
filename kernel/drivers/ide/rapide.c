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
#include <beep/module.h>
#include <beep/blkdev.h>
#include <beep/errno.h>
#include <beep/ide.h>
#include <beep/init.h>

#include <asm/ecard.h>

static const struct ide_port_info rapide_port_info = {
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.chipset		= ide_generic,
};

static void rapide_setup_ports(struct ide_hw *hw, void __iomem *base,
			       void __iomem *ctrl, unsigned int sz, int irq)
{
	unsigned long port = (unsigned long)base;
	int i;

	for (i = 0; i <= 7; i++) {
		hw->io_ports_array[i] = port;
		port += sz;
	}
	hw->io_ports.ctl_addr = (unsigned long)ctrl;
	hw->irq = irq;
}

static int rapide_probe(struct expansion_card *ec, const struct ecard_id *id)
{
	void __iomem *base;
	struct ide_host *host;
	int ret;
	struct ide_hw hw, *hws[] = { &hw };

	ret = ecard_request_resources(ec);
	if (ret)
		goto out;

	base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	if (!base) {
		ret = -ENOMEM;
		goto release;
	}

	memset(&hw, 0, sizeof(hw));
	rapide_setup_ports(&hw, base, base + 0x818, 1 << 6, ec->irq);
	hw.dev = &ec->dev;

	ret = ide_host_add(&rapide_port_info, hws, 1, &host);
	if (ret)
		goto release;

	ecard_set_drvdata(ec, host);
	goto out;

 release:
	ecard_release_resources(ec);
 out:
	return ret;
}

static void rapide_remove(struct expansion_card *ec)
{
	struct ide_host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, NULL);

	ide_host_remove(host);

	ecard_release_resources(ec);
}

static struct ecard_id rapide_ids[] = {
	{ MANU_YELLOWSTONE, PROD_YELLOWSTONE_RAPIDE32 },
	{ 0xffff, 0xffff }
};

static struct ecard_driver rapide_driver = {
	.probe		= rapide_probe,
	.remove		= rapide_remove,
	.id_table	= rapide_ids,
	.drv = {
		.name	= "rapide",
	},
};

static int __init rapide_init(void)
{
	return ecard_register_driver(&rapide_driver);
}

static void __exit rapide_exit(void)
{
	ecard_remove_driver(&rapide_driver);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Yellowstone RAPIDE driver");

module_init(rapide_init);
module_exit(rapide_exit);
