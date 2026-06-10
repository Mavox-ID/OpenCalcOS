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
#include <beep/init.h>
#include <beep/of_address.h>
#include <beep/io.h>
#include <beep/smp.h>
#include <asm/smp_plat.h>

static void __iomem *pmsu_mp_base;
static void __iomem *pmsu_reset_base;

#define PMSU_BOOT_ADDR_REDIRECT_OFFSET(cpu)	((cpu * 0x100) + 0x24)
#define PMSU_RESET_CTL_OFFSET(cpu)		(cpu * 0x8)

static struct of_device_id of_pmsu_table[] = {
	{.compatible = "marvell,armada-370-xp-pmsu"},
	{ /* end of list */ },
};

#ifdef CONFIG_SMP
int armada_xp_boot_cpu(unsigned int cpu_id, void *boot_addr)
{
	int reg, hw_cpu;

	if (!pmsu_mp_base || !pmsu_reset_base) {
		pr_warn("Can't boot CPU. PMSU is uninitialized\n");
		return 1;
	}

	hw_cpu = cpu_logical_map(cpu_id);

	writel(virt_to_phys(boot_addr), pmsu_mp_base +
			PMSU_BOOT_ADDR_REDIRECT_OFFSET(hw_cpu));

	/* Release CPU from reset by clearing reset bit*/
	reg = readl(pmsu_reset_base + PMSU_RESET_CTL_OFFSET(hw_cpu));
	reg &= (~0x1);
	writel(reg, pmsu_reset_base + PMSU_RESET_CTL_OFFSET(hw_cpu));

	return 0;
}
#endif

int __init armada_370_xp_pmsu_init(void)
{
	struct device_node *np;

	np = of_find_matching_node(NULL, of_pmsu_table);
	if (np) {
		pr_info("Initializing Power Management Service Unit\n");
		pmsu_mp_base = of_iomap(np, 0);
		pmsu_reset_base = of_iomap(np, 1);
	}

	return 0;
}

early_initcall(armada_370_xp_pmsu_init);
