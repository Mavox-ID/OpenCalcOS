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
#ifndef __X86_IRQ_REMAPPING_H
#define __X86_IRQ_REMAPPING_H

#include <asm/io_apic.h>

#ifdef CONFIG_IRQ_REMAP

extern int irq_remapping_enabled;

extern void setup_irq_remapping_ops(void);
extern int irq_remapping_supported(void);
extern int irq_remapping_prepare(void);
extern int irq_remapping_enable(void);
extern void irq_remapping_disable(void);
extern int irq_remapping_reenable(int);
extern int irq_remap_enable_fault_handling(void);
extern int setup_ioapic_remapped_entry(int irq,
				       struct IO_APIC_route_entry *entry,
				       unsigned int destination,
				       int vector,
				       struct io_apic_irq_attr *attr);
extern int set_remapped_irq_affinity(struct irq_data *data,
				     const struct cpumask *mask,
				     bool force);
extern void free_remapped_irq(int irq);
extern void compose_remapped_msi_msg(struct pci_dev *pdev,
				     unsigned int irq, unsigned int dest,
				     struct msi_msg *msg, u8 hpet_id);
extern int msi_alloc_remapped_irq(struct pci_dev *pdev, int irq, int nvec);
extern int msi_setup_remapped_irq(struct pci_dev *pdev, unsigned int irq,
				  int index, int sub_handle);
extern int setup_hpet_msi_remapped(unsigned int irq, unsigned int id);

#else  /* CONFIG_IRQ_REMAP */

#define irq_remapping_enabled	0

static inline void setup_irq_remapping_ops(void) { }
static inline int irq_remapping_supported(void) { return 0; }
static inline int irq_remapping_prepare(void) { return -ENODEV; }
static inline int irq_remapping_enable(void) { return -ENODEV; }
static inline void irq_remapping_disable(void) { }
static inline int irq_remapping_reenable(int eim) { return -ENODEV; }
static inline int irq_remap_enable_fault_handling(void) { return -ENODEV; }
static inline int setup_ioapic_remapped_entry(int irq,
					      struct IO_APIC_route_entry *entry,
					      unsigned int destination,
					      int vector,
					      struct io_apic_irq_attr *attr)
{
	return -ENODEV;
}
static inline int set_remapped_irq_affinity(struct irq_data *data,
					    const struct cpumask *mask,
					    bool force)
{
	return 0;
}
static inline void free_remapped_irq(int irq) { }
static inline void compose_remapped_msi_msg(struct pci_dev *pdev,
					    unsigned int irq, unsigned int dest,
					    struct msi_msg *msg, u8 hpet_id)
{
}
static inline int msi_alloc_remapped_irq(struct pci_dev *pdev, int irq, int nvec)
{
	return -ENODEV;
}
static inline int msi_setup_remapped_irq(struct pci_dev *pdev, unsigned int irq,
					 int index, int sub_handle)
{
	return -ENODEV;
}
static inline int setup_hpet_msi_remapped(unsigned int irq, unsigned int id)
{
	return -ENODEV;
}
#endif /* CONFIG_IRQ_REMAP */

#endif /* __X86_IRQ_REMAPPING_H */
