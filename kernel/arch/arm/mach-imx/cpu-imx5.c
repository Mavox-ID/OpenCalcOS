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
#include <beep/init.h>
#include <beep/module.h>
#include <beep/io.h>

#include "hardware.h"

static int mx5_cpu_rev = -1;

#define IIM_SREV 0x24
#define MX50_HW_ADADIG_DIGPROG	0xB0

static int get_mx51_srev(void)
{
	void __iomem *iim_base = MX51_IO_ADDRESS(MX51_IIM_BASE_ADDR);
	u32 rev = readl(iim_base + IIM_SREV) & 0xff;

	switch (rev) {
	case 0x0:
		return IMX_CHIP_REVISION_2_0;
	case 0x10:
		return IMX_CHIP_REVISION_3_0;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}

/*
 * Returns:
 *	the silicon revision of the cpu
 *	-EINVAL - not a mx51
 */
int mx51_revision(void)
{
	if (!cpu_is_mx51())
		return -EINVAL;

	if (mx5_cpu_rev == -1)
		mx5_cpu_rev = get_mx51_srev();

	return mx5_cpu_rev;
}
EXPORT_SYMBOL(mx51_revision);

#ifdef CONFIG_NEON

/*
 * All versions of the silicon before Rev. 3 have broken NEON implementations.
 * Dependent on link order - so the assumption is that vfp_init is called
 * before us.
 */
int __init mx51_neon_fixup(void)
{
	if (mx51_revision() < IMX_CHIP_REVISION_3_0 &&
			(elf_hwcap & HWCAP_NEON)) {
		elf_hwcap &= ~HWCAP_NEON;
		pr_info("Turning off NEON support, detected broken NEON implementation\n");
	}
	return 0;
}

#endif

static int get_mx53_srev(void)
{
	void __iomem *iim_base = MX51_IO_ADDRESS(MX53_IIM_BASE_ADDR);
	u32 rev = readl(iim_base + IIM_SREV) & 0xff;

	switch (rev) {
	case 0x0:
		return IMX_CHIP_REVISION_1_0;
	case 0x2:
		return IMX_CHIP_REVISION_2_0;
	case 0x3:
		return IMX_CHIP_REVISION_2_1;
	default:
		return IMX_CHIP_REVISION_UNKNOWN;
	}
}

/*
 * Returns:
 *	the silicon revision of the cpu
 *	-EINVAL - not a mx53
 */
int mx53_revision(void)
{
	if (!cpu_is_mx53())
		return -EINVAL;

	if (mx5_cpu_rev == -1)
		mx5_cpu_rev = get_mx53_srev();

	return mx5_cpu_rev;
}
EXPORT_SYMBOL(mx53_revision);

static int get_mx50_srev(void)
{
	void __iomem *anatop = ioremap(MX50_ANATOP_BASE_ADDR, SZ_8K);
	u32 rev;

	if (!anatop) {
		mx5_cpu_rev = -EINVAL;
		return 0;
	}

	rev = readl(anatop + MX50_HW_ADADIG_DIGPROG);
	rev &= 0xff;

	iounmap(anatop);
	if (rev == 0x0)
		return IMX_CHIP_REVISION_1_0;
	else if (rev == 0x1)
		return IMX_CHIP_REVISION_1_1;
	return 0;
}

/*
 * Returns:
 *	the silicon revision of the cpu
 *	-EINVAL - not a mx50
 */
int mx50_revision(void)
{
	if (!cpu_is_mx50())
		return -EINVAL;

	if (mx5_cpu_rev == -1)
		mx5_cpu_rev = get_mx50_srev();

	return mx5_cpu_rev;
}
EXPORT_SYMBOL(mx50_revision);
