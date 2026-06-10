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
#ifndef __ASM_ARCH_DEVICES_H
#define __ASM_ARCH_DEVICES_H

#include <beep/pci.h>

 /* Ethernet */
extern void __init ks8695_add_device_wan(void);
extern void __init ks8695_add_device_lan(void);
extern void __init ks8695_add_device_hpna(void);

 /* PCI */
#define KS8695_MODE_PCI		0
#define KS8695_MODE_MINIPCI	1
#define KS8695_MODE_CARDBUS	2

struct ks8695_pci_cfg {
	short mode;
	int (*map_irq)(const struct pci_dev *, u8, u8);
};
extern __init void ks8695_init_pci(struct ks8695_pci_cfg *);

#endif
