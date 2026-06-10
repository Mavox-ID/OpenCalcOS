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
#ifndef __ICS_H
#define __ICS_H

#define XIVE_ADDR_MASK		0x7FFULL

extern void wsp_init_irq(void);

extern int wsp_ics_alloc_irq(struct device_node *dn, int num);
extern void wsp_ics_free_irq(struct device_node *dn, unsigned int irq);

#ifdef CONFIG_PCI_MSI
extern void wsp_ics_set_msi_chip(unsigned int irq);
extern void wsp_ics_set_std_chip(unsigned int irq);
#endif /* CONFIG_PCI_MSI */

#endif /* __ICS_H */
