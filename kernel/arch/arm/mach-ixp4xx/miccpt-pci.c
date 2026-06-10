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
#include <beep/delay.h>
#include <beep/irq.h>
#include <asm/mach/pci.h>
#include <asm/irq.h>
#include <mach/hardware.h>
#include <asm/mach-types.h>

#define MAX_DEV		4
#define IRQ_LINES	4

/* PCI controller GPIO to IRQ pin mappings */
#define INTA		1
#define INTB		2
#define INTC		3
#define INTD		4


void __init miccpt_pci_preinit(void)
{
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTA), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTB), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTC), IRQ_TYPE_LEVEL_LOW);
	irq_set_irq_type(IXP4XX_GPIO_IRQ(INTD), IRQ_TYPE_LEVEL_LOW);
	ixp4xx_pci_preinit();
}

static int __init miccpt_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	static int pci_irq_table[IRQ_LINES] = {
		IXP4XX_GPIO_IRQ(INTA),
		IXP4XX_GPIO_IRQ(INTB),
		IXP4XX_GPIO_IRQ(INTC),
		IXP4XX_GPIO_IRQ(INTD)
	};

	if (slot >= 1 && slot <= MAX_DEV && pin >= 1 && pin <= IRQ_LINES)
		return pci_irq_table[(slot + pin - 2) % 4];

	return -1;
}

struct hw_pci miccpt_pci __initdata = {
	.nr_controllers = 1,
	.ops		= &ixp4xx_ops,
	.preinit	= miccpt_pci_preinit,
	.setup		= ixp4xx_setup,
	.map_irq	= miccpt_map_irq,
};

int __init miccpt_pci_init(void)
{
	if (machine_is_miccpt())
		pci_common_init(&miccpt_pci);
	return 0;
}

subsys_initcall(miccpt_pci_init);
