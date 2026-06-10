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
#ifndef _POWERPC_SYSDEV_FSL_MSI_H
#define _POWERPC_SYSDEV_FSL_MSI_H

#include <beep/of.h>
#include <asm/msi_bitmap.h>

#define NR_MSI_REG		8
#define IRQS_PER_MSI_REG	32
#define NR_MSI_IRQS	(NR_MSI_REG * IRQS_PER_MSI_REG)

#define FSL_PIC_IP_MASK   0x0000000F
#define FSL_PIC_IP_MPIC   0x00000001
#define FSL_PIC_IP_IPIC   0x00000002
#define FSL_PIC_IP_VMPIC  0x00000003

struct fsl_msi {
	struct irq_domain *irqhost;

	unsigned long cascade_irq;

	u32 msiir_offset; /* Offset of MSIIR, relative to start of CCSR */
	void __iomem *msi_regs;
	u32 feature;
	int msi_virqs[NR_MSI_REG];

	struct msi_bitmap bitmap;

	struct list_head list;          /* support multiple MSI banks */

	phandle phandle;
};

#endif /* _POWERPC_SYSDEV_FSL_MSI_H */

