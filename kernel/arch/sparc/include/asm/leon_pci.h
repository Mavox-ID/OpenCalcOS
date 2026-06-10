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
#ifndef _ASM_LEON_PCI_H_
#define _ASM_LEON_PCI_H_

/* PCI related definitions */
struct leon_pci_info {
	struct pci_ops *ops;
	struct resource	io_space;
	struct resource	mem_space;
	int (*map_irq)(const struct pci_dev *dev, u8 slot, u8 pin);
};

extern void leon_pci_init(struct platform_device *ofdev,
				struct leon_pci_info *info);

#endif /* _ASM_LEON_PCI_H_ */
