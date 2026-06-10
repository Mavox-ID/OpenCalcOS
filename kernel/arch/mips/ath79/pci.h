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
#ifndef _ATH79_PCI_H
#define _ATH79_PCI_H

struct ath79_pci_irq {
	u8	slot;
	u8	pin;
	int	irq;
};

#ifdef CONFIG_PCI
void ath79_pci_set_irq_map(unsigned nr_irqs, const struct ath79_pci_irq *map);
void ath79_pci_set_plat_dev_init(int (*func)(struct pci_dev *dev));
int ath79_register_pci(void);
#else
static inline void
ath79_pci_set_irq_map(unsigned nr_irqs, const struct ath79_pci_irq *map) {}
static inline void
ath79_pci_set_plat_dev_init(int (*func)(struct pci_dev *)) {}
static inline int ath79_register_pci(void) { return 0; }
#endif

#endif /* _ATH79_PCI_H */
