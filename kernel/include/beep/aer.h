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
#ifndef _AER_H_
#define _AER_H_

struct aer_header_log_regs {
	unsigned int dw0;
	unsigned int dw1;
	unsigned int dw2;
	unsigned int dw3;
};

struct aer_capability_regs {
	u32 header;
	u32 uncor_status;
	u32 uncor_mask;
	u32 uncor_severity;
	u32 cor_status;
	u32 cor_mask;
	u32 cap_control;
	struct aer_header_log_regs header_log;
	u32 root_command;
	u32 root_status;
	u16 cor_err_source;
	u16 uncor_err_source;
};

#if defined(CONFIG_PCIEAER)
/* pci-e port driver needs this function to enable aer */
extern int pci_enable_pcie_error_reporting(struct pci_dev *dev);
extern int pci_disable_pcie_error_reporting(struct pci_dev *dev);
extern int pci_cleanup_aer_uncorrect_error_status(struct pci_dev *dev);
#else
static inline int pci_enable_pcie_error_reporting(struct pci_dev *dev)
{
	return -EINVAL;
}
static inline int pci_disable_pcie_error_reporting(struct pci_dev *dev)
{
	return -EINVAL;
}
static inline int pci_cleanup_aer_uncorrect_error_status(struct pci_dev *dev)
{
	return -EINVAL;
}
#endif

extern void cper_print_aer(const char *prefix, int cper_severity,
			   struct aer_capability_regs *aer);
extern int cper_severity_to_aer(int cper_severity);
extern void aer_recover_queue(int domain, unsigned int bus, unsigned int devfn,
			      int severity);
#endif //_AER_H_

