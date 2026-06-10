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
#include <beep/bootmem.h>
#include <asm/bootinfo.h>
#include <bcm63xx_board.h>
#include <bcm63xx_cpu.h>
#include <bcm63xx_io.h>
#include <bcm63xx_regs.h>
#include <bcm63xx_gpio.h>

void __init prom_init(void)
{
	u32 reg, mask;

	bcm63xx_cpu_init();

	/* stop any running watchdog */
	bcm_wdt_writel(WDT_STOP_1, WDT_CTL_REG);
	bcm_wdt_writel(WDT_STOP_2, WDT_CTL_REG);

	/* disable all hardware blocks clock for now */
	if (BCMCPU_IS_6328())
		mask = CKCTL_6328_ALL_SAFE_EN;
	else if (BCMCPU_IS_6338())
		mask = CKCTL_6338_ALL_SAFE_EN;
	else if (BCMCPU_IS_6345())
		mask = CKCTL_6345_ALL_SAFE_EN;
	else if (BCMCPU_IS_6348())
		mask = CKCTL_6348_ALL_SAFE_EN;
	else if (BCMCPU_IS_6358())
		mask = CKCTL_6358_ALL_SAFE_EN;
	else if (BCMCPU_IS_6368())
		mask = CKCTL_6368_ALL_SAFE_EN;
	else
		mask = 0;

	reg = bcm_perf_readl(PERF_CKCTL_REG);
	reg &= ~mask;
	bcm_perf_writel(reg, PERF_CKCTL_REG);

	/* register gpiochip */
	bcm63xx_gpio_init();

	/* do low level board init */
	board_prom_init();
}

void __init prom_free_prom_memory(void)
{
}
