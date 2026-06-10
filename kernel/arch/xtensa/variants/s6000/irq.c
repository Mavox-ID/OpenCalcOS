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
#include <asm/irq.h>
#include <variant/hardware.h>

/* S6_REG_INTC */
#define INTC_STATUS	0x000
#define INTC_RAW	0x010
#define INTC_STATUS_AG	0x100
#define INTC_CFG(n)	(0x200 + 4 * (n))

/*
 * The s6000 has a crossbar that multiplexes interrupt output lines
 * from the peripherals to input lines on the xtensa core.
 *
 * We leave the mapping decisions to the platform as it depends on the
 * actually connected peripherals which distribution makes sense.
 */
extern const signed char *platform_irq_mappings[NR_IRQS];

static unsigned long scp_to_intc_enable[] = {
#define	TO_INTC_ENABLE(n)	(((n) << 1) + 1)
	TO_INTC_ENABLE(0),
	TO_INTC_ENABLE(1),
	TO_INTC_ENABLE(2),
	TO_INTC_ENABLE(3),
	TO_INTC_ENABLE(4),
	TO_INTC_ENABLE(5),
	TO_INTC_ENABLE(6),
	TO_INTC_ENABLE(7),
	TO_INTC_ENABLE(8),
	TO_INTC_ENABLE(9),
	TO_INTC_ENABLE(10),
	TO_INTC_ENABLE(11),
	TO_INTC_ENABLE(12),
	-1,
	-1,
	TO_INTC_ENABLE(13),
	-1,
	TO_INTC_ENABLE(14),
	-1,
	TO_INTC_ENABLE(15),
#undef	TO_INTC_ENABLE
};

static void irq_set(unsigned int irq, int enable)
{
	unsigned long en;
	const signed char *m = platform_irq_mappings[irq];

	if (!m)
		return;
	en = enable ? scp_to_intc_enable[irq] : 0;
	while (*m >= 0) {
		writel(en, S6_REG_INTC + INTC_CFG(*m));
		m++;
	}
}

void variant_irq_enable(unsigned int irq)
{
	irq_set(irq, 1);
}

void variant_irq_disable(unsigned int irq)
{
	irq_set(irq, 0);
}
