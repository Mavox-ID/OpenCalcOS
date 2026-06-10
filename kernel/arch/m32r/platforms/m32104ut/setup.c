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
#include <beep/irq.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/device.h>

#include <asm/m32r.h>
#include <asm/io.h>

#define irq2port(x) (M32R_ICU_CR1_PORTL + ((x - 1) * sizeof(unsigned long)))

icu_data_t icu_data[NR_IRQS];

static void disable_m32104ut_irq(unsigned int irq)
{
	unsigned long port, data;

	port = irq2port(irq);
	data = icu_data[irq].icucr|M32R_ICUCR_ILEVEL7;
	outl(data, port);
}

static void enable_m32104ut_irq(unsigned int irq)
{
	unsigned long port, data;

	port = irq2port(irq);
	data = icu_data[irq].icucr|M32R_ICUCR_IEN|M32R_ICUCR_ILEVEL6;
	outl(data, port);
}

static void mask_m32104ut_irq(struct irq_data *data)
{
	disable_m32104ut_irq(data->irq);
}

static void unmask_m32104ut_irq(struct irq_data *data)
{
	enable_m32104ut_irq(data->irq);
}

static void shutdown_m32104ut_irq(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned long port = irq2port(irq);

	outl(M32R_ICUCR_ILEVEL7, port);
}

static struct irq_chip m32104ut_irq_type =
{
	.name		= "M32104UT-IRQ",
	.irq_shutdown	= shutdown_m32104ut_irq,
	.irq_unmask	= unmask_m32104ut_irq,
	.irq_mask	= mask_m32104ut_irq,
};

void __init init_IRQ(void)
{
	static int once = 0;

	if (once)
		return;
	else
		once++;

#if defined(CONFIG_SMC91X)
	/* INT#0: LAN controller on M32104UT-LAN (SMC91C111)*/
	irq_set_chip_and_handler(M32R_IRQ_INT0, &m32104ut_irq_type,
				 handle_level_irq);
	/* "H" level sense */
	cu_data[M32R_IRQ_INT0].icucr = M32R_ICUCR_IEN | M32R_ICUCR_ISMOD11;
	disable_m32104ut_irq(M32R_IRQ_INT0);
#endif  /* CONFIG_SMC91X */

	/* MFT2 : system timer */
	irq_set_chip_and_handler(M32R_IRQ_MFT2, &m32104ut_irq_type,
				 handle_level_irq);
	icu_data[M32R_IRQ_MFT2].icucr = M32R_ICUCR_IEN;
	disable_m32104ut_irq(M32R_IRQ_MFT2);

#ifdef CONFIG_SERIAL_M32R_SIO
	/* SIO0_R : uart receive data */
	irq_set_chip_and_handler(M32R_IRQ_SIO0_R, &m32104ut_irq_type,
				 handle_level_irq);
	icu_data[M32R_IRQ_SIO0_R].icucr = M32R_ICUCR_IEN;
	disable_m32104ut_irq(M32R_IRQ_SIO0_R);

	/* SIO0_S : uart send data */
	irq_set_chip_and_handler(M32R_IRQ_SIO0_S, &m32104ut_irq_type,
				 handle_level_irq);
	icu_data[M32R_IRQ_SIO0_S].icucr = M32R_ICUCR_IEN;
	disable_m32104ut_irq(M32R_IRQ_SIO0_S);
#endif /* CONFIG_SERIAL_M32R_SIO */
}

#if defined(CONFIG_SMC91X)

#define LAN_IOSTART     0x300
#define LAN_IOEND       0x320
static struct resource smc91x_resources[] = {
	[0] = {
		.start  = (LAN_IOSTART),
		.end    = (LAN_IOEND),
		.flags  = IORESOURCE_MEM,
	},
	[1] = {
		.start  = M32R_IRQ_INT0,
		.end    = M32R_IRQ_INT0,
		.flags  = IORESOURCE_IRQ,
	}
};

static struct platform_device smc91x_device = {
	.name		= "smc91x",
	.id		= 0,
	.num_resources  = ARRAY_SIZE(smc91x_resources),
	.resource       = smc91x_resources,
};
#endif

static int __init platform_init(void)
{
#if defined(CONFIG_SMC91X)
	platform_device_register(&smc91x_device);
#endif
	return 0;
}
arch_initcall(platform_init);
