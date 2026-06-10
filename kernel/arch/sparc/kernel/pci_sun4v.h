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
#ifndef _PCI_SUN4V_H
#define _PCI_SUN4V_H

extern long pci_sun4v_iommu_map(unsigned long devhandle,
				unsigned long tsbid,
				unsigned long num_ttes,
				unsigned long io_attributes,
				unsigned long io_page_list_pa);
extern unsigned long pci_sun4v_iommu_demap(unsigned long devhandle,
					   unsigned long tsbid,
					   unsigned long num_ttes);
extern unsigned long pci_sun4v_iommu_getmap(unsigned long devhandle,
					    unsigned long tsbid,
					    unsigned long *io_attributes,
					    unsigned long *real_address);
extern unsigned long pci_sun4v_config_get(unsigned long devhandle,
					  unsigned long pci_device,
					  unsigned long config_offset,
					  unsigned long size);
extern int pci_sun4v_config_put(unsigned long devhandle,
				unsigned long pci_device,
				unsigned long config_offset,
				unsigned long size,
				unsigned long data);

extern unsigned long pci_sun4v_msiq_conf(unsigned long devhandle,
					 unsigned long msiqid,
					 unsigned long msiq_paddr,
					 unsigned long num_entries);
extern unsigned long pci_sun4v_msiq_info(unsigned long devhandle,
					 unsigned long msiqid,
					 unsigned long *msiq_paddr,
					 unsigned long *num_entries);
extern unsigned long pci_sun4v_msiq_getvalid(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long *valid);
extern unsigned long pci_sun4v_msiq_setvalid(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long valid);
extern unsigned long pci_sun4v_msiq_getstate(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long *state);
extern unsigned long pci_sun4v_msiq_setstate(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long state);
extern unsigned long pci_sun4v_msiq_gethead(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long *head);
extern unsigned long pci_sun4v_msiq_sethead(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long head);
extern unsigned long pci_sun4v_msiq_gettail(unsigned long devhandle,
					     unsigned long msiqid,
					     unsigned long *head);
extern unsigned long pci_sun4v_msi_getvalid(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long *valid);
extern unsigned long pci_sun4v_msi_setvalid(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long valid);
extern unsigned long pci_sun4v_msi_getmsiq(unsigned long devhandle,
					   unsigned long msinum,
					   unsigned long *msiq);
extern unsigned long pci_sun4v_msi_setmsiq(unsigned long devhandle,
					   unsigned long msinum,
					   unsigned long msiq,
					   unsigned long msitype);
extern unsigned long pci_sun4v_msi_getstate(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long *state);
extern unsigned long pci_sun4v_msi_setstate(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long state);
extern unsigned long pci_sun4v_msg_getmsiq(unsigned long devhandle,
					   unsigned long msinum,
					   unsigned long *msiq);
extern unsigned long pci_sun4v_msg_setmsiq(unsigned long devhandle,
					   unsigned long msinum,
					   unsigned long msiq);
extern unsigned long pci_sun4v_msg_getvalid(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long *valid);
extern unsigned long pci_sun4v_msg_setvalid(unsigned long devhandle,
					    unsigned long msinum,
					    unsigned long valid);

#endif /* !(_PCI_SUN4V_H) */
