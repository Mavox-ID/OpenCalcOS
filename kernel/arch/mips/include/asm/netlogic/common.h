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
#ifndef _NETLOGIC_COMMON_H_
#define _NETLOGIC_COMMON_H_

/*
 * Common SMP definitions
 */
#define	RESET_VEC_PHYS		0x1fc00000
#define	RESET_DATA_PHYS		(RESET_VEC_PHYS + (1<<10))
#define	BOOT_THREAD_MODE	0
#define	BOOT_NMI_LOCK		4
#define	BOOT_NMI_HANDLER	8

#ifndef __ASSEMBLY__
#include <beep/cpumask.h>
#include <beep/spinlock.h>
#include <asm/irq.h>
#include <asm/mach-netlogic/multi-node.h>

struct irq_desc;
void nlm_smp_function_ipi_handler(unsigned int irq, struct irq_desc *desc);
void nlm_smp_resched_ipi_handler(unsigned int irq, struct irq_desc *desc);
void nlm_smp_irq_init(int hwcpuid);
void nlm_boot_secondary_cpus(void);
int nlm_wakeup_secondary_cpus(void);
void nlm_rmiboot_preboot(void);
void nlm_percpu_init(int hwcpuid);

static inline void
nlm_set_nmi_handler(void *handler)
{
	char *reset_data;

	reset_data = (char *)CKSEG1ADDR(RESET_DATA_PHYS);
	*(int64_t *)(reset_data + BOOT_NMI_HANDLER) = (long)handler;
}

/*
 * Misc.
 */
unsigned int nlm_get_cpu_frequency(void);
void nlm_node_init(int node);
extern struct plat_smp_ops nlm_smp_ops;
extern char nlm_reset_entry[], nlm_reset_entry_end[];

extern unsigned int nlm_threads_per_core;
extern cpumask_t nlm_cpumask;

struct nlm_soc_info {
	unsigned long coremask;	/* cores enabled on the soc */
	unsigned long ebase;
	uint64_t irqmask;
	uint64_t sysbase;	/* only for XLP */
	uint64_t picbase;
	spinlock_t piclock;
};

#define	nlm_get_node(i)		(&nlm_nodes[i])
#ifdef CONFIG_CPU_XLR
#define	nlm_current_node()	(&nlm_nodes[0])
#else
#define nlm_current_node()	(&nlm_nodes[nlm_nodeid()])
#endif

struct irq_data;
uint64_t nlm_pci_irqmask(int node);
void nlm_set_pic_extra_ack(int node, int irq,  void (*xack)(struct irq_data *));

/*
 * The NR_IRQs is divided between nodes, each of them has a separate irq space
 */
static inline int nlm_irq_to_xirq(int node, int irq)
{
	return node * NR_IRQS / NLM_NR_NODES + irq;
}

extern struct nlm_soc_info nlm_nodes[NLM_NR_NODES];
extern int nlm_cpu_ready[];
#endif
#endif /* _NETLOGIC_COMMON_H_ */
