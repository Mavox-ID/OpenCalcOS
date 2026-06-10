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
#include <beep/kernel.h>
#include <beep/module.h>

#include <asm/mach-jz4740/base.h>
#include <asm/mach-jz4740/timer.h>

void __iomem *jz4740_timer_base;
EXPORT_SYMBOL_GPL(jz4740_timer_base);

void jz4740_timer_enable_watchdog(void)
{
	writel(BIT(16), jz4740_timer_base + JZ_REG_TIMER_STOP_CLEAR);
}
EXPORT_SYMBOL_GPL(jz4740_timer_enable_watchdog);

void jz4740_timer_disable_watchdog(void)
{
	writel(BIT(16), jz4740_timer_base + JZ_REG_TIMER_STOP_SET);
}
EXPORT_SYMBOL_GPL(jz4740_timer_disable_watchdog);

void __init jz4740_timer_init(void)
{
	jz4740_timer_base = ioremap(JZ4740_TCU_BASE_ADDR, 0x100);

	if (!jz4740_timer_base)
		panic("Failed to ioremap timer registers");

	/* Disable all timer clocks except for those used as system timers */
	writel(0x000100fc, jz4740_timer_base + JZ_REG_TIMER_STOP_SET);

	/* Timer irqs are unmasked by default, mask them */
	writel(0x00ff00ff, jz4740_timer_base + JZ_REG_TIMER_MASK_SET);
}
