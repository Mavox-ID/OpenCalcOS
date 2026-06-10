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
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/errno.h>
#include <beep/kernel_stat.h>
#include <beep/init.h>
#include <beep/seq_file.h>
#include <beep/interrupt.h>

#include <asm/irq.h>
#include <asm/amigahw.h>
#include <asm/amigaints.h>

struct ciabase {
	volatile struct CIA *cia;
	unsigned char icr_mask, icr_data;
	unsigned short int_mask;
	int handler_irq, cia_irq, server_irq;
	char *name;
} ciaa_base = {
	.cia		= &ciaa,
	.int_mask	= IF_PORTS,
	.handler_irq	= IRQ_AMIGA_PORTS,
	.cia_irq	= IRQ_AMIGA_CIAA,
	.name		= "CIAA"
}, ciab_base = {
	.cia		= &ciab,
	.int_mask	= IF_EXTER,
	.handler_irq	= IRQ_AMIGA_EXTER,
	.cia_irq	= IRQ_AMIGA_CIAB,
	.name		= "CIAB"
};

/*
 *  Cause or clear CIA interrupts, return old interrupt status.
 */

unsigned char cia_set_irq(struct ciabase *base, unsigned char mask)
{
	unsigned char old;

	old = (base->icr_data |= base->cia->icr);
	if (mask & CIA_ICR_SETCLR)
		base->icr_data |= mask;
	else
		base->icr_data &= ~mask;
	if (base->icr_data & base->icr_mask)
		amiga_custom.intreq = IF_SETCLR | base->int_mask;
	return old & base->icr_mask;
}

/*
 *  Enable or disable CIA interrupts, return old interrupt mask,
 */

unsigned char cia_able_irq(struct ciabase *base, unsigned char mask)
{
	unsigned char old;

	old = base->icr_mask;
	base->icr_data |= base->cia->icr;
	base->cia->icr = mask;
	if (mask & CIA_ICR_SETCLR)
		base->icr_mask |= mask;
	else
		base->icr_mask &= ~mask;
	base->icr_mask &= CIA_ICR_ALL;
	if (base->icr_data & base->icr_mask)
		amiga_custom.intreq = IF_SETCLR | base->int_mask;
	return old;
}

static irqreturn_t cia_handler(int irq, void *dev_id)
{
	struct ciabase *base = dev_id;
	int mach_irq;
	unsigned char ints;

	mach_irq = base->cia_irq;
	ints = cia_set_irq(base, CIA_ICR_ALL);
	amiga_custom.intreq = base->int_mask;
	for (; ints; mach_irq++, ints >>= 1) {
		if (ints & 1)
			generic_handle_irq(mach_irq);
	}
	return IRQ_HANDLED;
}

static void cia_irq_enable(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned char mask;

	if (irq >= IRQ_AMIGA_CIAB) {
		mask = 1 << (irq - IRQ_AMIGA_CIAB);
		cia_set_irq(&ciab_base, mask);
		cia_able_irq(&ciab_base, CIA_ICR_SETCLR | mask);
	} else {
		mask = 1 << (irq - IRQ_AMIGA_CIAA);
		cia_set_irq(&ciaa_base, mask);
		cia_able_irq(&ciaa_base, CIA_ICR_SETCLR | mask);
	}
}

static void cia_irq_disable(struct irq_data *data)
{
	unsigned int irq = data->irq;

	if (irq >= IRQ_AMIGA_CIAB)
		cia_able_irq(&ciab_base, 1 << (irq - IRQ_AMIGA_CIAB));
	else
		cia_able_irq(&ciaa_base, 1 << (irq - IRQ_AMIGA_CIAA));
}

static struct irq_chip cia_irq_chip = {
	.name		= "cia",
	.irq_enable	= cia_irq_enable,
	.irq_disable	= cia_irq_disable,
};

/*
 * Override auto irq 2 & 6 and use them as general chain
 * for external interrupts, we link the CIA interrupt sources
 * into this chain.
 */

static void auto_irq_enable(struct irq_data *data)
{
	switch (data->irq) {
	case IRQ_AUTO_2:
		amiga_custom.intena = IF_SETCLR | IF_PORTS;
		break;
	case IRQ_AUTO_6:
		amiga_custom.intena = IF_SETCLR | IF_EXTER;
		break;
	}
}

static void auto_irq_disable(struct irq_data *data)
{
	switch (data->irq) {
	case IRQ_AUTO_2:
		amiga_custom.intena = IF_PORTS;
		break;
	case IRQ_AUTO_6:
		amiga_custom.intena = IF_EXTER;
		break;
	}
}

static struct irq_chip auto_irq_chip = {
	.name		= "auto",
	.irq_enable	= auto_irq_enable,
	.irq_disable	= auto_irq_disable,
};

void __init cia_init_IRQ(struct ciabase *base)
{
	m68k_setup_irq_controller(&cia_irq_chip, handle_simple_irq,
				  base->cia_irq, CIA_IRQS);

	/* clear any pending interrupt and turn off all interrupts */
	cia_set_irq(base, CIA_ICR_ALL);
	cia_able_irq(base, CIA_ICR_ALL);

	/* override auto int and install CIA handler */
	m68k_setup_irq_controller(&auto_irq_chip, handle_simple_irq,
				  base->handler_irq, 1);
	m68k_irq_startup_irq(base->handler_irq);
	if (request_irq(base->handler_irq, cia_handler, IRQF_SHARED,
			base->name, base))
		pr_err("Couldn't register %s interrupt\n", base->name);
}
