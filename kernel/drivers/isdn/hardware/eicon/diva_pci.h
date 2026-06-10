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
#ifndef __DIVA_PCI_INTERFACE_H__
#define __DIVA_PCI_INTERFACE_H__

void __iomem *divasa_remap_pci_bar(diva_os_xdi_adapter_t *a,
				   int id,
				   unsigned long bar,
				   unsigned long area_length);
void divasa_unmap_pci_bar(void __iomem *bar);
unsigned long divasa_get_pci_irq(unsigned char bus,
				 unsigned char func, void *pci_dev_handle);
unsigned long divasa_get_pci_bar(unsigned char bus,
				 unsigned char func,
				 int bar, void *pci_dev_handle);
byte diva_os_get_pci_bus(void *pci_dev_handle);
byte diva_os_get_pci_func(void *pci_dev_handle);

#endif
