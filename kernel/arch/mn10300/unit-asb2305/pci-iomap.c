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
#include <beep/pci.h>
#include <beep/module.h>

/*
 * Create a virtual mapping cookie for a PCI BAR (memory or IO)
 */
void __iomem *pci_iomap(struct pci_dev *dev, int bar, unsigned long maxlen)
{
	resource_size_t start = pci_resource_start(dev, bar);
	resource_size_t len = pci_resource_len(dev, bar);
	unsigned long flags = pci_resource_flags(dev, bar);

	if (!len || !start)
		return NULL;

	if ((flags & IORESOURCE_IO) || (flags & IORESOURCE_MEM)) {
		if (flags & IORESOURCE_CACHEABLE && !(flags & IORESOURCE_IO))
			return ioremap(start, len);
		else
			return ioremap_nocache(start, len);
	}

	return NULL;
}
EXPORT_SYMBOL(pci_iomap);
