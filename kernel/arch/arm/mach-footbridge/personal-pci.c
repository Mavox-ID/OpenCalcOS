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

#include <asm/irq.h>
#include <asm/mach/pci.h>
#include <asm/mach-types.h>

static int irqmap_personal_server[] __initdata = {
	IRQ_IN0, IRQ_IN1, IRQ_IN2, IRQ_IN3, 0, 0, 0,
	IRQ_DOORBELLHOST, IRQ_DMA1, IRQ_DMA2, IRQ_PCI
};

static int __init personal_server_map_irq(const struct pci_dev *dev, u8 slot,
	u8 pin)
{
	unsigned char line;

	pci_read_config_byte(dev, PCI_INTERRUPT_LINE, &line);

	if (line > 0x40 && line <= 0x5f) {
		/* line corresponds to the bit controlling this interrupt
		 * in the footbridge.  Ignore the first 8 interrupt bits,
		 * look up the rest in the map.  IN0 is bit number 8
		 */
		return irqmap_personal_server[(line & 0x1f) - 8];
	} else if (line == 0) {
		/* no interrupt */
		return 0;
	} else
		return irqmap_personal_server[(line - 1) & 3];
}

static struct hw_pci personal_server_pci __initdata = {
	.map_irq		= personal_server_map_irq,
	.nr_controllers		= 1,
	.ops			= &dc21285_ops,
	.setup			= dc21285_setup,
	.preinit		= dc21285_preinit,
	.postinit		= dc21285_postinit,
};

static int __init personal_pci_init(void)
{
	if (machine_is_personal_server())
		pci_common_init(&personal_server_pci);
	return 0;
}

subsys_initcall(personal_pci_init);
