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
#include <beep/io.h>
#include <beep/cpumask.h>
#include <beep/bitops.h>

#include <asm/cacheflush.h>
#include <asm/hardware/cache-l2x0.h>

#include "iomap.h"
#include "irammap.h"
#include "reset.h"
#include "sleep.h"
#include "fuse.h"

#define TEGRA_IRAM_RESET_BASE (TEGRA_IRAM_BASE + \
				TEGRA_IRAM_RESET_HANDLER_OFFSET)

static bool is_enabled;

static void __init tegra_cpu_reset_handler_enable(void)
{
	void __iomem *iram_base = IO_ADDRESS(TEGRA_IRAM_RESET_BASE);
	void __iomem *evp_cpu_reset =
		IO_ADDRESS(TEGRA_EXCEPTION_VECTORS_BASE + 0x100);
	void __iomem *sb_ctrl = IO_ADDRESS(TEGRA_SB_BASE);
	u32 reg;

	BUG_ON(is_enabled);
	BUG_ON(tegra_cpu_reset_handler_size > TEGRA_IRAM_RESET_HANDLER_SIZE);

	memcpy(iram_base, (void *)__tegra_cpu_reset_handler_start,
			tegra_cpu_reset_handler_size);

	/*
	 * NOTE: This must be the one and only write to the EVP CPU reset
	 *       vector in the entire system.
	 */
	writel(TEGRA_IRAM_RESET_BASE + tegra_cpu_reset_handler_offset,
			evp_cpu_reset);
	wmb();
	reg = readl(evp_cpu_reset);

	/*
	 * Prevent further modifications to the physical reset vector.
	 *  NOTE: Has no effect on chips prior to Tegra30.
	 */
	if (tegra_chip_id != TEGRA20) {
		reg = readl(sb_ctrl);
		reg |= 2;
		writel(reg, sb_ctrl);
		wmb();
	}

	is_enabled = true;
}

void __init tegra_cpu_reset_handler_init(void)
{

#ifdef CONFIG_SMP
	__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_PRESENT] =
		*((u32 *)cpu_present_mask);
	__tegra_cpu_reset_handler_data[TEGRA_RESET_STARTUP_SECONDARY] =
		virt_to_phys((void *)tegra_secondary_startup);
#endif

#ifdef CONFIG_PM_SLEEP
	__tegra_cpu_reset_handler_data[TEGRA_RESET_STARTUP_LP2] =
		virt_to_phys((void *)tegra_resume);
#endif

	tegra_cpu_reset_handler_enable();
}
