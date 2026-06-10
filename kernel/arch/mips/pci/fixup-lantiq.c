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
#include <beep/of_irq.h>
#include <beep/of_pci.h>

int (*ltq_pci_plat_arch_init)(struct pci_dev *dev) = NULL;
int (*ltq_pci_plat_dev_init)(struct pci_dev *dev) = NULL;

int pcibios_plat_dev_init(struct pci_dev *dev)
{
	if (ltq_pci_plat_arch_init)
		return ltq_pci_plat_arch_init(dev);

	if (ltq_pci_plat_dev_init)
		return ltq_pci_plat_dev_init(dev);

	return 0;
}

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	struct of_irq dev_irq;
	int irq;

	if (of_irq_map_pci(dev, &dev_irq)) {
		dev_err(&dev->dev, "trying to map irq for unknown slot:%d pin:%d\n",
			slot, pin);
		return 0;
	}
	irq = irq_create_of_mapping(dev_irq.controller, dev_irq.specifier,
					dev_irq.size);
	dev_info(&dev->dev, "SLOT:%d PIN:%d IRQ:%d\n", slot, pin, irq);
	return irq;
}
