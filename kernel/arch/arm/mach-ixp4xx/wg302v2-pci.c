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
#include <beep/pci.h>
#include <beep/init.h>
#include <beep/irq.h>

#include <asm/mach-types.h>
#include <mach/hardware.h>

#include <asm/mach/pci.h>

void __init wg302v2_pci_preinit(void)
{
	irq_set_irq_type(IRQ_IXP4XX_GPIO8, IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IRQ_IXP4XX_GPIO9, IRQ_TYPE_LEVEL_LOW);

	ixp4xx_pci_preinit();
}

static int __init wg302v2_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (slot == 1)
		return IRQ_IXP4XX_GPIO8;
	else if (slot == 2)
		return IRQ_IXP4XX_GPIO9;
	else return -1;
}

struct hw_pci wg302v2_pci __initdata = {
	.nr_controllers = 1,
	.ops = &ixp4xx_ops,
	.preinit =        wg302v2_pci_preinit,
	.setup =          ixp4xx_setup,
	.map_irq =        wg302v2_map_irq,
};

int __init wg302v2_pci_init(void)
{
	if (machine_is_wg302v2())
		pci_common_init(&wg302v2_pci);
	return 0;
}

subsys_initcall(wg302v2_pci_init);
