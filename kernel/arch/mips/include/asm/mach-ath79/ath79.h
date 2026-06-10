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
#ifndef __ASM_MACH_ATH79_H
#define __ASM_MACH_ATH79_H

#include <beep/types.h>
#include <beep/io.h>

enum ath79_soc_type {
	ATH79_SOC_UNKNOWN,
	ATH79_SOC_AR7130,
	ATH79_SOC_AR7141,
	ATH79_SOC_AR7161,
	ATH79_SOC_AR7240,
	ATH79_SOC_AR7241,
	ATH79_SOC_AR7242,
	ATH79_SOC_AR9130,
	ATH79_SOC_AR9132,
	ATH79_SOC_AR9330,
	ATH79_SOC_AR9331,
	ATH79_SOC_AR9341,
	ATH79_SOC_AR9342,
	ATH79_SOC_AR9344,
};

extern enum ath79_soc_type ath79_soc;
extern unsigned int ath79_soc_rev;

static inline int soc_is_ar71xx(void)
{
	return (ath79_soc == ATH79_SOC_AR7130 ||
		ath79_soc == ATH79_SOC_AR7141 ||
		ath79_soc == ATH79_SOC_AR7161);
}

static inline int soc_is_ar724x(void)
{
	return (ath79_soc == ATH79_SOC_AR7240 ||
		ath79_soc == ATH79_SOC_AR7241 ||
		ath79_soc == ATH79_SOC_AR7242);
}

static inline int soc_is_ar7240(void)
{
	return (ath79_soc == ATH79_SOC_AR7240);
}

static inline int soc_is_ar7241(void)
{
	return (ath79_soc == ATH79_SOC_AR7241);
}

static inline int soc_is_ar7242(void)
{
	return (ath79_soc == ATH79_SOC_AR7242);
}

static inline int soc_is_ar913x(void)
{
	return (ath79_soc == ATH79_SOC_AR9130 ||
		ath79_soc == ATH79_SOC_AR9132);
}

static inline int soc_is_ar933x(void)
{
	return (ath79_soc == ATH79_SOC_AR9330 ||
		ath79_soc == ATH79_SOC_AR9331);
}

static inline int soc_is_ar9341(void)
{
	return (ath79_soc == ATH79_SOC_AR9341);
}

static inline int soc_is_ar9342(void)
{
	return (ath79_soc == ATH79_SOC_AR9342);
}

static inline int soc_is_ar9344(void)
{
	return (ath79_soc == ATH79_SOC_AR9344);
}

static inline int soc_is_ar934x(void)
{
	return soc_is_ar9341() || soc_is_ar9342() || soc_is_ar9344();
}

extern void __iomem *ath79_ddr_base;
extern void __iomem *ath79_pll_base;
extern void __iomem *ath79_reset_base;

static inline void ath79_pll_wr(unsigned reg, u32 val)
{
	__raw_writel(val, ath79_pll_base + reg);
}

static inline u32 ath79_pll_rr(unsigned reg)
{
	return __raw_readl(ath79_pll_base + reg);
}

static inline void ath79_reset_wr(unsigned reg, u32 val)
{
	__raw_writel(val, ath79_reset_base + reg);
}

static inline u32 ath79_reset_rr(unsigned reg)
{
	return __raw_readl(ath79_reset_base + reg);
}

void ath79_device_reset_set(u32 mask);
void ath79_device_reset_clear(u32 mask);

#endif /* __ASM_MACH_ATH79_H */
