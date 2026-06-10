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
#include <beep/io.h>
#include <beep/slab.h>
#include <beep/of_address.h>
#include <beep/of_irq.h>
#include <beep/irqdomain.h>
#include <beep/irqchip/bcm2835.h>

#include <asm/exception.h>

/* Put the bank and irq (32 bits) into the hwirq */
#define MAKE_HWIRQ(b, n)	((b << 5) | (n))
#define HWIRQ_BANK(i)		(i >> 5)
#define HWIRQ_BIT(i)		BIT(i & 0x1f)

#define NR_IRQS_BANK0		8
#define BANK0_HWIRQ_MASK	0xff
/* Shortcuts can't be disabled so any unknown new ones need to be masked */
#define SHORTCUT1_MASK		0x00007c00
#define SHORTCUT2_MASK		0x001f8000
#define SHORTCUT_SHIFT		10
#define BANK1_HWIRQ		BIT(8)
#define BANK2_HWIRQ		BIT(9)
#define BANK0_VALID_MASK	(BANK0_HWIRQ_MASK | BANK1_HWIRQ | BANK2_HWIRQ \
					| SHORTCUT1_MASK | SHORTCUT2_MASK)

#define REG_FIQ_CONTROL		0x0c

#define NR_BANKS		3
#define IRQS_PER_BANK		32

static int reg_pending[] __initconst = { 0x00, 0x04, 0x08 };
static int reg_enable[] __initconst = { 0x18, 0x10, 0x14 };
static int reg_disable[] __initconst = { 0x24, 0x1c, 0x20 };
static int bank_irqs[] __initconst = { 8, 32, 32 };

static const int shortcuts[] = {
	7, 9, 10, 18, 19,		/* Bank 1 */
	21, 22, 23, 24, 25, 30		/* Bank 2 */
};

struct armctrl_ic {
	void __iomem *base;
	void __iomem *pending[NR_BANKS];
	void __iomem *enable[NR_BANKS];
	void __iomem *disable[NR_BANKS];
	struct irq_domain *domain;
};

static struct armctrl_ic intc __read_mostly;

static void armctrl_mask_irq(struct irq_data *d)
{
	writel_relaxed(HWIRQ_BIT(d->hwirq), intc.disable[HWIRQ_BANK(d->hwirq)]);
}

static void armctrl_unmask_irq(struct irq_data *d)
{
	writel_relaxed(HWIRQ_BIT(d->hwirq), intc.enable[HWIRQ_BANK(d->hwirq)]);
}

static struct irq_chip armctrl_chip = {
	.name = "ARMCTRL-level",
	.irq_mask = armctrl_mask_irq,
	.irq_unmask = armctrl_unmask_irq
};

static int armctrl_xlate(struct irq_domain *d, struct device_node *ctrlr,
	const u32 *intspec, unsigned int intsize,
	unsigned long *out_hwirq, unsigned int *out_type)
{
	if (WARN_ON(intsize != 2))
		return -EINVAL;

	if (WARN_ON(intspec[0] >= NR_BANKS))
		return -EINVAL;

	if (WARN_ON(intspec[1] >= IRQS_PER_BANK))
		return -EINVAL;

	if (WARN_ON(intspec[0] == 0 && intspec[1] >= NR_IRQS_BANK0))
		return -EINVAL;

	*out_hwirq = MAKE_HWIRQ(intspec[0], intspec[1]);
	*out_type = IRQ_TYPE_NONE;
	return 0;
}

static struct irq_domain_ops armctrl_ops = {
	.xlate = armctrl_xlate
};

static int __init armctrl_of_init(struct device_node *node,
	struct device_node *parent)
{
	void __iomem *base;
	int irq, b, i;

	base = of_iomap(node, 0);
	if (!base)
		panic("%s: unable to map IC registers\n",
			node->full_name);

	intc.domain = irq_domain_add_linear(node, MAKE_HWIRQ(NR_BANKS, 0),
			&armctrl_ops, NULL);
	if (!intc.domain)
		panic("%s: unable to create IRQ domain\n", node->full_name);

	for (b = 0; b < NR_BANKS; b++) {
		intc.pending[b] = base + reg_pending[b];
		intc.enable[b] = base + reg_enable[b];
		intc.disable[b] = base + reg_disable[b];

		for (i = 0; i < bank_irqs[b]; i++) {
			irq = irq_create_mapping(intc.domain, MAKE_HWIRQ(b, i));
			BUG_ON(irq <= 0);
			irq_set_chip_and_handler(irq, &armctrl_chip,
				handle_level_irq);
			set_irq_flags(irq, IRQF_VALID | IRQF_PROBE);
		}
	}
	return 0;
}

static struct of_device_id irq_of_match[] __initconst = {
	{ .compatible = "brcm,bcm2835-armctrl-ic", .data = armctrl_of_init },
	{ }
};

void __init bcm2835_init_irq(void)
{
	of_irq_init(irq_of_match);
}

/*
 * Handle each interrupt across the entire interrupt controller.  This reads the
 * status register before handling each interrupt, which is necessary given that
 * handle_IRQ may briefly re-enable interrupts for soft IRQ handling.
 */

static void armctrl_handle_bank(int bank, struct pt_regs *regs)
{
	u32 stat, irq;

	while ((stat = readl_relaxed(intc.pending[bank]))) {
		irq = MAKE_HWIRQ(bank, ffs(stat) - 1);
		handle_IRQ(irq_linear_revmap(intc.domain, irq), regs);
	}
}

static void armctrl_handle_shortcut(int bank, struct pt_regs *regs,
	u32 stat)
{
	u32 irq = MAKE_HWIRQ(bank, shortcuts[ffs(stat >> SHORTCUT_SHIFT) - 1]);
	handle_IRQ(irq_linear_revmap(intc.domain, irq), regs);
}

asmlinkage void __exception_irq_entry bcm2835_handle_irq(
	struct pt_regs *regs)
{
	u32 stat, irq;

	while ((stat = readl_relaxed(intc.pending[0]) & BANK0_VALID_MASK)) {
		if (stat & BANK0_HWIRQ_MASK) {
			irq = MAKE_HWIRQ(0, ffs(stat & BANK0_HWIRQ_MASK) - 1);
			handle_IRQ(irq_linear_revmap(intc.domain, irq), regs);
		} else if (stat & SHORTCUT1_MASK) {
			armctrl_handle_shortcut(1, regs, stat & SHORTCUT1_MASK);
		} else if (stat & SHORTCUT2_MASK) {
			armctrl_handle_shortcut(2, regs, stat & SHORTCUT2_MASK);
		} else if (stat & BANK1_HWIRQ) {
			armctrl_handle_bank(1, regs);
		} else if (stat & BANK2_HWIRQ) {
			armctrl_handle_bank(2, regs);
		} else {
			BUG();
		}
	}
}
