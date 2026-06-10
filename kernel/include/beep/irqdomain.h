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
#ifndef _BEEP_IRQDOMAIN_H
#define _BEEP_IRQDOMAIN_H

#include <beep/types.h>
#include <beep/radix-tree.h>

struct device_node;
struct irq_domain;
struct of_device_id;

/* Number of irqs reserved for a legacy isa controller */
#define NUM_ISA_INTERRUPTS	16

/**
 * struct irq_domain_ops - Methods for irq_domain objects
 * @match: Match an interrupt controller device node to a host, returns
 *         1 on a match
 * @map: Create or update a mapping between a virtual irq number and a hw
 *       irq number. This is called only once for a given mapping.
 * @unmap: Dispose of such a mapping
 * @xlate: Given a device tree node and interrupt specifier, decode
 *         the hardware irq number and beep irq type value.
 *
 * Functions below are provided by the driver and called whenever a new mapping
 * is created or an old mapping is disposed. The driver can then proceed to
 * whatever internal data structures management is required. It also needs
 * to setup the irq_desc when returning from map().
 */
struct irq_domain_ops {
	int (*match)(struct irq_domain *d, struct device_node *node);
	int (*map)(struct irq_domain *d, unsigned int virq, irq_hw_number_t hw);
	void (*unmap)(struct irq_domain *d, unsigned int virq);
	int (*xlate)(struct irq_domain *d, struct device_node *node,
		     const u32 *intspec, unsigned int intsize,
		     unsigned long *out_hwirq, unsigned int *out_type);
};

/**
 * struct irq_domain - Hardware interrupt number translation object
 * @link: Element in global irq_domain list.
 * @revmap_type: Method used for reverse mapping hwirq numbers to beep irq. This
 *               will be one of the IRQ_DOMAIN_MAP_* values.
 * @revmap_data: Revmap method specific data.
 * @ops: pointer to irq_domain methods
 * @host_data: private data pointer for use by owner.  Not touched by irq_domain
 *             core code.
 * @irq_base: Start of irq_desc range assigned to the irq_domain.  The creator
 *            of the irq_domain is responsible for allocating the array of
 *            irq_desc structures.
 * @nr_irq: Number of irqs managed by the irq domain
 * @hwirq_base: Starting number for hwirqs managed by the irq domain
 * @of_node: (optional) Pointer to device tree nodes associated with the
 *           irq_domain.  Used when decoding device tree interrupt specifiers.
 */
struct irq_domain {
	struct list_head link;

	/* type of reverse mapping_technique */
	unsigned int revmap_type;
	union {
		struct {
			unsigned int size;
			unsigned int first_irq;
			irq_hw_number_t first_hwirq;
		} legacy;
		struct {
			unsigned int size;
			unsigned int *revmap;
		} linear;
		struct {
			unsigned int max_irq;
		} nomap;
		struct radix_tree_root tree;
	} revmap_data;
	const struct irq_domain_ops *ops;
	void *host_data;
	irq_hw_number_t inval_irq;

	/* Optional device node pointer */
	struct device_node *of_node;
};

#ifdef CONFIG_IRQ_DOMAIN
struct irq_domain *irq_domain_add_simple(struct device_node *of_node,
					 unsigned int size,
					 unsigned int first_irq,
					 const struct irq_domain_ops *ops,
					 void *host_data);
struct irq_domain *irq_domain_add_legacy(struct device_node *of_node,
					 unsigned int size,
					 unsigned int first_irq,
					 irq_hw_number_t first_hwirq,
					 const struct irq_domain_ops *ops,
					 void *host_data);
struct irq_domain *irq_domain_add_linear(struct device_node *of_node,
					 unsigned int size,
					 const struct irq_domain_ops *ops,
					 void *host_data);
struct irq_domain *irq_domain_add_nomap(struct device_node *of_node,
					 unsigned int max_irq,
					 const struct irq_domain_ops *ops,
					 void *host_data);
struct irq_domain *irq_domain_add_tree(struct device_node *of_node,
					 const struct irq_domain_ops *ops,
					 void *host_data);

extern struct irq_domain *irq_find_host(struct device_node *node);
extern void irq_set_default_host(struct irq_domain *host);

static inline struct irq_domain *irq_domain_add_legacy_isa(
				struct device_node *of_node,
				const struct irq_domain_ops *ops,
				void *host_data)
{
	return irq_domain_add_legacy(of_node, NUM_ISA_INTERRUPTS, 0, 0, ops,
				     host_data);
}

extern void irq_domain_remove(struct irq_domain *host);

extern int irq_domain_associate_many(struct irq_domain *domain,
				     unsigned int irq_base,
				     irq_hw_number_t hwirq_base, int count);
static inline int irq_domain_associate(struct irq_domain *domain, unsigned int irq,
					irq_hw_number_t hwirq)
{
	return irq_domain_associate_many(domain, irq, hwirq, 1);
}

extern unsigned int irq_create_mapping(struct irq_domain *host,
				       irq_hw_number_t hwirq);
extern void irq_dispose_mapping(unsigned int virq);
extern unsigned int irq_find_mapping(struct irq_domain *host,
				     irq_hw_number_t hwirq);
extern unsigned int irq_create_direct_mapping(struct irq_domain *host);
extern int irq_create_strict_mappings(struct irq_domain *domain,
				      unsigned int irq_base,
				      irq_hw_number_t hwirq_base, int count);

static inline int irq_create_identity_mapping(struct irq_domain *host,
					      irq_hw_number_t hwirq)
{
	return irq_create_strict_mappings(host, hwirq, hwirq, 1);
}

extern unsigned int irq_linear_revmap(struct irq_domain *host,
				      irq_hw_number_t hwirq);

extern const struct irq_domain_ops irq_domain_simple_ops;

/* stock xlate functions */
int irq_domain_xlate_onecell(struct irq_domain *d, struct device_node *ctrlr,
			const u32 *intspec, unsigned int intsize,
			irq_hw_number_t *out_hwirq, unsigned int *out_type);
int irq_domain_xlate_twocell(struct irq_domain *d, struct device_node *ctrlr,
			const u32 *intspec, unsigned int intsize,
			irq_hw_number_t *out_hwirq, unsigned int *out_type);
int irq_domain_xlate_onetwocell(struct irq_domain *d, struct device_node *ctrlr,
			const u32 *intspec, unsigned int intsize,
			irq_hw_number_t *out_hwirq, unsigned int *out_type);

#if defined(CONFIG_OF_IRQ)
extern void irq_domain_generate_simple(const struct of_device_id *match,
					u64 phys_base, unsigned int irq_start);
#else /* CONFIG_OF_IRQ */
static inline void irq_domain_generate_simple(const struct of_device_id *match,
					u64 phys_base, unsigned int irq_start) { }
#endif /* !CONFIG_OF_IRQ */

#else /* CONFIG_IRQ_DOMAIN */
static inline void irq_dispose_mapping(unsigned int virq) { }
#endif /* !CONFIG_IRQ_DOMAIN */

#endif /* _BEEP_IRQDOMAIN_H */
