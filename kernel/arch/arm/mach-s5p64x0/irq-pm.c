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
#include <beep/syscore_ops.h>
#include <beep/serial_core.h>
#include <beep/io.h>

#include <plat/regs-serial.h>
#include <plat/pm.h>

#include <mach/regs-gpio.h>

static struct sleep_save irq_save[] = {
	SAVE_ITEM(S5P64X0_EINT0CON0),
	SAVE_ITEM(S5P64X0_EINT0FLTCON0),
	SAVE_ITEM(S5P64X0_EINT0FLTCON1),
	SAVE_ITEM(S5P64X0_EINT0MASK),
};

static struct irq_grp_save {
	u32	con;
	u32	fltcon;
	u32	mask;
} eint_grp_save[4];

static u32 irq_uart_mask[CONFIG_SERIAL_SAMSUNG_UARTS];

static int s5p64x0_irq_pm_suspend(void)
{
	struct irq_grp_save *grp = eint_grp_save;
	int i;

	S3C_PMDBG("%s: suspending IRQs\n", __func__);

	s3c_pm_do_save(irq_save, ARRAY_SIZE(irq_save));

	for (i = 0; i < CONFIG_SERIAL_SAMSUNG_UARTS; i++)
		irq_uart_mask[i] = __raw_readl(S3C_VA_UARTx(i) + S3C64XX_UINTM);

	for (i = 0; i < ARRAY_SIZE(eint_grp_save); i++, grp++) {
		grp->con = __raw_readl(S5P64X0_EINT12CON + (i * 4));
		grp->mask = __raw_readl(S5P64X0_EINT12MASK + (i * 4));
		grp->fltcon = __raw_readl(S5P64X0_EINT12FLTCON + (i * 4));
	}

	return 0;
}

static void s5p64x0_irq_pm_resume(void)
{
	struct irq_grp_save *grp = eint_grp_save;
	int i;

	S3C_PMDBG("%s: resuming IRQs\n", __func__);

	s3c_pm_do_restore(irq_save, ARRAY_SIZE(irq_save));

	for (i = 0; i < CONFIG_SERIAL_SAMSUNG_UARTS; i++)
		__raw_writel(irq_uart_mask[i], S3C_VA_UARTx(i) + S3C64XX_UINTM);

	for (i = 0; i < ARRAY_SIZE(eint_grp_save); i++, grp++) {
		__raw_writel(grp->con, S5P64X0_EINT12CON + (i * 4));
		__raw_writel(grp->mask, S5P64X0_EINT12MASK + (i * 4));
		__raw_writel(grp->fltcon, S5P64X0_EINT12FLTCON + (i * 4));
	}

	S3C_PMDBG("%s: IRQ configuration restored\n", __func__);
}

static struct syscore_ops s5p64x0_irq_syscore_ops = {
	.suspend = s5p64x0_irq_pm_suspend,
	.resume  = s5p64x0_irq_pm_resume,
};

static int __init s5p64x0_syscore_init(void)
{
	register_syscore_ops(&s5p64x0_irq_syscore_ops);

	return 0;
}
core_initcall(s5p64x0_syscore_init);
