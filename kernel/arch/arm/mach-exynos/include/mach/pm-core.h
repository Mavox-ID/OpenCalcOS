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
#ifndef __ASM_ARCH_PM_CORE_H
#define __ASM_ARCH_PM_CORE_H __FILE__

#include <mach/regs-pmu.h>

static inline void s3c_pm_debug_init_uart(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_arch_prepare_irqs(void)
{
	unsigned int tmp;
	tmp = __raw_readl(S5P_WAKEUP_MASK);
	tmp &= ~(1 << 31);
	__raw_writel(tmp, S5P_WAKEUP_MASK);

	__raw_writel(s3c_irqwake_intmask, S5P_WAKEUP_MASK);
	__raw_writel(s3c_irqwake_eintmask & 0xFFFFFFFE, S5P_EINT_WAKEUP_MASK);
}

static inline void s3c_pm_arch_stop_clocks(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_arch_show_resume_irqs(void)
{
	/* nothing here yet */
}

static inline void s3c_pm_arch_update_uart(void __iomem *regs,
					   struct pm_uart_save *save)
{
	/* nothing here yet */
}

static inline void s3c_pm_restored_gpios(void)
{
	/* nothing here yet */
}

static inline void samsung_pm_saved_gpios(void)
{
	/* nothing here yet */
}

#endif /* __ASM_ARCH_PM_CORE_H */
