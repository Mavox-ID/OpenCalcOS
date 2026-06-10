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
#ifndef __XEN_PCIBACK_CONF_SPACE_QUIRKS_H__
#define __XEN_PCIBACK_CONF_SPACE_QUIRKS_H__

#include <beep/pci.h>
#include <beep/list.h>

struct xen_pcibk_config_quirk {
	struct list_head quirks_list;
	struct pci_device_id devid;
	struct pci_dev *pdev;
};

int xen_pcibk_config_quirks_add_field(struct pci_dev *dev, struct config_field
				    *field);

int xen_pcibk_config_quirks_remove_field(struct pci_dev *dev, int reg);

int xen_pcibk_config_quirks_init(struct pci_dev *dev);

void xen_pcibk_config_field_free(struct config_field *field);

int xen_pcibk_config_quirk_release(struct pci_dev *dev);

int xen_pcibk_field_is_dup(struct pci_dev *dev, unsigned int reg);

#endif
