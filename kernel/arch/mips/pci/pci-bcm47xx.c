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
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/ssb/ssb.h>
#include <beep/bcma/bcma.h>
#include <bcm47xx.h>

int __init pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	return 0;
}

#ifdef CONFIG_BCM47XX_SSB
static int bcm47xx_pcibios_plat_dev_init_ssb(struct pci_dev *dev)
{
	int res;
	u8 slot, pin;

	res = ssb_pcibios_plat_dev_init(dev);
	if (res < 0) {
		printk(KERN_ALERT "PCI: Failed to init device %s\n",
		       pci_name(dev));
		return res;
	}

	pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	slot = PCI_SLOT(dev->devfn);
	res = ssb_pcibios_map_irq(dev, slot, pin);

	/* IRQ-0 and IRQ-1 are software interrupts. */
	if (res < 2) {
		printk(KERN_ALERT "PCI: Failed to map IRQ of device %s\n",
		       pci_name(dev));
		return res;
	}

	dev->irq = res;
	return 0;
}
#endif

#ifdef CONFIG_BCM47XX_BCMA
static int bcm47xx_pcibios_plat_dev_init_bcma(struct pci_dev *dev)
{
	int res;

	res = bcma_core_pci_plat_dev_init(dev);
	if (res < 0) {
		printk(KERN_ALERT "PCI: Failed to init device %s\n",
		       pci_name(dev));
		return res;
	}

	res = bcma_core_pci_pcibios_map_irq(dev);

	/* IRQ-0 and IRQ-1 are software interrupts. */
	if (res < 2) {
		printk(KERN_ALERT "PCI: Failed to map IRQ of device %s\n",
		       pci_name(dev));
		return res;
	}

	dev->irq = res;
	return 0;
}
#endif

int pcibios_plat_dev_init(struct pci_dev *dev)
{
#ifdef CONFIG_BCM47XX_SSB
	if (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_SSB)
		return bcm47xx_pcibios_plat_dev_init_ssb(dev);
	else
#endif
#ifdef CONFIG_BCM47XX_BCMA
	if  (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_BCMA)
		return bcm47xx_pcibios_plat_dev_init_bcma(dev);
	else
#endif
		return 0;
}
