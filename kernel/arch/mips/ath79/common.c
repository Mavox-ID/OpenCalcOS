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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/types.h>
#include <beep/spinlock.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>
#include "common.h"

static DEFINE_SPINLOCK(ath79_device_reset_lock);

u32 ath79_cpu_freq;
EXPORT_SYMBOL_GPL(ath79_cpu_freq);

u32 ath79_ahb_freq;
EXPORT_SYMBOL_GPL(ath79_ahb_freq);

u32 ath79_ddr_freq;
EXPORT_SYMBOL_GPL(ath79_ddr_freq);

enum ath79_soc_type ath79_soc;
unsigned int ath79_soc_rev;

void __iomem *ath79_pll_base;
void __iomem *ath79_reset_base;
EXPORT_SYMBOL_GPL(ath79_reset_base);
void __iomem *ath79_ddr_base;

void ath79_ddr_wb_flush(u32 reg)
{
	void __iomem *flush_reg = ath79_ddr_base + reg;

	/* Flush the DDR write buffer. */
	__raw_writel(0x1, flush_reg);
	while (__raw_readl(flush_reg) & 0x1)
		;

	/* It must be run twice. */
	__raw_writel(0x1, flush_reg);
	while (__raw_readl(flush_reg) & 0x1)
		;
}
EXPORT_SYMBOL_GPL(ath79_ddr_wb_flush);

void ath79_device_reset_set(u32 mask)
{
	unsigned long flags;
	u32 reg;
	u32 t;

	if (soc_is_ar71xx())
		reg = AR71XX_RESET_REG_RESET_MODULE;
	else if (soc_is_ar724x())
		reg = AR724X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar913x())
		reg = AR913X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar933x())
		reg = AR933X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar934x())
		reg = AR934X_RESET_REG_RESET_MODULE;
	else
		BUG();

	spin_lock_irqsave(&ath79_device_reset_lock, flags);
	t = ath79_reset_rr(reg);
	ath79_reset_wr(reg, t | mask);
	spin_unlock_irqrestore(&ath79_device_reset_lock, flags);
}
EXPORT_SYMBOL_GPL(ath79_device_reset_set);

void ath79_device_reset_clear(u32 mask)
{
	unsigned long flags;
	u32 reg;
	u32 t;

	if (soc_is_ar71xx())
		reg = AR71XX_RESET_REG_RESET_MODULE;
	else if (soc_is_ar724x())
		reg = AR724X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar913x())
		reg = AR913X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar933x())
		reg = AR933X_RESET_REG_RESET_MODULE;
	else if (soc_is_ar934x())
		reg = AR934X_RESET_REG_RESET_MODULE;
	else
		BUG();

	spin_lock_irqsave(&ath79_device_reset_lock, flags);
	t = ath79_reset_rr(reg);
	ath79_reset_wr(reg, t & ~mask);
	spin_unlock_irqrestore(&ath79_device_reset_lock, flags);
}
EXPORT_SYMBOL_GPL(ath79_device_reset_clear);
