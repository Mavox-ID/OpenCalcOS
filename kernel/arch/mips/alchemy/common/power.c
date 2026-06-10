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
#include <beep/pm.h>
#include <beep/sysctl.h>
#include <beep/jiffies.h>

#include <asm/uaccess.h>
#include <asm/mach-au1x00/au1000.h>

/*
 * We need to save/restore a bunch of core registers that are
 * either volatile or reset to some state across a processor sleep.
 * If reading a register doesn't provide a proper result for a
 * later restore, we have to provide a function for loading that
 * register and save a copy.
 *
 * We only have to save/restore registers that aren't otherwise
 * done as part of a driver pm_* function.
 */
static unsigned int sleep_sys_clocks[5];
static unsigned int sleep_sys_pinfunc;
static unsigned int sleep_static_memctlr[4][3];


static void save_core_regs(void)
{
	/* Clocks and PLLs. */
	sleep_sys_clocks[0] = au_readl(SYS_FREQCTRL0);
	sleep_sys_clocks[1] = au_readl(SYS_FREQCTRL1);
	sleep_sys_clocks[2] = au_readl(SYS_CLKSRC);
	sleep_sys_clocks[3] = au_readl(SYS_CPUPLL);
	sleep_sys_clocks[4] = au_readl(SYS_AUXPLL);

	/* pin mux config */
	sleep_sys_pinfunc = au_readl(SYS_PINFUNC);

	/* Save the static memory controller configuration. */
	sleep_static_memctlr[0][0] = au_readl(MEM_STCFG0);
	sleep_static_memctlr[0][1] = au_readl(MEM_STTIME0);
	sleep_static_memctlr[0][2] = au_readl(MEM_STADDR0);
	sleep_static_memctlr[1][0] = au_readl(MEM_STCFG1);
	sleep_static_memctlr[1][1] = au_readl(MEM_STTIME1);
	sleep_static_memctlr[1][2] = au_readl(MEM_STADDR1);
	sleep_static_memctlr[2][0] = au_readl(MEM_STCFG2);
	sleep_static_memctlr[2][1] = au_readl(MEM_STTIME2);
	sleep_static_memctlr[2][2] = au_readl(MEM_STADDR2);
	sleep_static_memctlr[3][0] = au_readl(MEM_STCFG3);
	sleep_static_memctlr[3][1] = au_readl(MEM_STTIME3);
	sleep_static_memctlr[3][2] = au_readl(MEM_STADDR3);
}

static void restore_core_regs(void)
{
	/* restore clock configuration.  Writing CPUPLL last will
	 * stall a bit and stabilize other clocks (unless this is
	 * one of those Au1000 with a write-only PLL, where we dont
	 * have a valid value)
	 */
	au_writel(sleep_sys_clocks[0], SYS_FREQCTRL0);
	au_writel(sleep_sys_clocks[1], SYS_FREQCTRL1);
	au_writel(sleep_sys_clocks[2], SYS_CLKSRC);
	au_writel(sleep_sys_clocks[4], SYS_AUXPLL);
	if (!au1xxx_cpu_has_pll_wo())
		au_writel(sleep_sys_clocks[3], SYS_CPUPLL);
	au_sync();

	au_writel(sleep_sys_pinfunc, SYS_PINFUNC);
	au_sync();

	/* Restore the static memory controller configuration. */
	au_writel(sleep_static_memctlr[0][0], MEM_STCFG0);
	au_writel(sleep_static_memctlr[0][1], MEM_STTIME0);
	au_writel(sleep_static_memctlr[0][2], MEM_STADDR0);
	au_writel(sleep_static_memctlr[1][0], MEM_STCFG1);
	au_writel(sleep_static_memctlr[1][1], MEM_STTIME1);
	au_writel(sleep_static_memctlr[1][2], MEM_STADDR1);
	au_writel(sleep_static_memctlr[2][0], MEM_STCFG2);
	au_writel(sleep_static_memctlr[2][1], MEM_STTIME2);
	au_writel(sleep_static_memctlr[2][2], MEM_STADDR2);
	au_writel(sleep_static_memctlr[3][0], MEM_STCFG3);
	au_writel(sleep_static_memctlr[3][1], MEM_STTIME3);
	au_writel(sleep_static_memctlr[3][2], MEM_STADDR3);
}

void au_sleep(void)
{
	save_core_regs();

	switch (alchemy_get_cputype()) {
	case ALCHEMY_CPU_AU1000:
	case ALCHEMY_CPU_AU1500:
	case ALCHEMY_CPU_AU1100:
		alchemy_sleep_au1000();
		break;
	case ALCHEMY_CPU_AU1550:
	case ALCHEMY_CPU_AU1200:
		alchemy_sleep_au1550();
		break;
	case ALCHEMY_CPU_AU1300:
		alchemy_sleep_au1300();
		break;
	}

	restore_core_regs();
}
