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
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/irq.h>

#include <asm/irq_cpu.h>
#include <asm/lasat/lasat.h>
#include <asm/lasat/lasatint.h>

#include <irq.h>

static volatile int *lasat_int_status;
static volatile int *lasat_int_mask;
static volatile int lasat_int_mask_shift;

void disable_lasat_irq(struct irq_data *d)
{
	unsigned int irq_nr = d->irq - LASAT_IRQ_BASE;

	*lasat_int_mask &= ~(1 << irq_nr) << lasat_int_mask_shift;
}

void enable_lasat_irq(struct irq_data *d)
{
	unsigned int irq_nr = d->irq - LASAT_IRQ_BASE;

	*lasat_int_mask |= (1 << irq_nr) << lasat_int_mask_shift;
}

static struct irq_chip lasat_irq_type = {
	.name = "Lasat",
	.irq_mask = disable_lasat_irq,
	.irq_unmask = enable_lasat_irq,
};

static inline int ls1bit32(unsigned int x)
{
	int b = 31, s;

	s = 16; if (x << 16 == 0) s = 0; b -= s; x <<= s;
	s =  8; if (x <<  8 == 0) s = 0; b -= s; x <<= s;
	s =  4; if (x <<  4 == 0) s = 0; b -= s; x <<= s;
	s =  2; if (x <<  2 == 0) s = 0; b -= s; x <<= s;
	s =  1; if (x <<  1 == 0) s = 0; b -= s;

	return b;
}

static unsigned long (*get_int_status)(void);

static unsigned long get_int_status_100(void)
{
	return *lasat_int_status & *lasat_int_mask;
}

static unsigned long get_int_status_200(void)
{
	unsigned long int_status;

	int_status = *lasat_int_status;
	int_status &= (int_status >> LASATINT_MASK_SHIFT_200) & 0xffff;
	return int_status;
}

asmlinkage void plat_irq_dispatch(void)
{
	unsigned long int_status;
	unsigned int cause = read_c0_cause();
	int irq;

	if (cause & CAUSEF_IP7) {	/* R4000 count / compare IRQ */
		do_IRQ(7);
		return;
	}

	int_status = get_int_status();

	/* if int_status == 0, then the interrupt has already been cleared */
	if (int_status) {
		irq = LASAT_IRQ_BASE + ls1bit32(int_status);

		do_IRQ(irq);
	}
}

static struct irqaction cascade = {
	.handler	= no_action,
	.name		= "cascade",
	.flags		= IRQF_NO_THREAD,
};

void __init arch_init_irq(void)
{
	int i;

	if (IS_LASAT_200()) {
		lasat_int_status = (void *)LASAT_INT_STATUS_REG_200;
		lasat_int_mask = (void *)LASAT_INT_MASK_REG_200;
		lasat_int_mask_shift = LASATINT_MASK_SHIFT_200;
		get_int_status = get_int_status_200;
		*lasat_int_mask &= 0xffff;
	} else {
		lasat_int_status = (void *)LASAT_INT_STATUS_REG_100;
		lasat_int_mask = (void *)LASAT_INT_MASK_REG_100;
		lasat_int_mask_shift = LASATINT_MASK_SHIFT_100;
		get_int_status = get_int_status_100;
		*lasat_int_mask = 0;
	}

	mips_cpu_irq_init();

	for (i = LASAT_IRQ_BASE; i <= LASAT_IRQ_END; i++)
		irq_set_chip_and_handler(i, &lasat_irq_type, handle_level_irq);

	setup_irq(LASAT_CASCADE_IRQ, &cascade);
}
