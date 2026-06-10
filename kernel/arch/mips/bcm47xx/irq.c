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
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <asm/irq_cpu.h>
#include <bcm47xx.h>

void plat_irq_dispatch(void)
{
	u32 cause;

	cause = read_c0_cause() & read_c0_status() & CAUSEF_IP;

	clear_c0_status(cause);

	if (cause & CAUSEF_IP7)
		do_IRQ(7);
	if (cause & CAUSEF_IP2)
		do_IRQ(2);
	if (cause & CAUSEF_IP3)
		do_IRQ(3);
	if (cause & CAUSEF_IP4)
		do_IRQ(4);
	if (cause & CAUSEF_IP5)
		do_IRQ(5);
	if (cause & CAUSEF_IP6)
		do_IRQ(6);
}

void __init arch_init_irq(void)
{
#ifdef CONFIG_BCM47XX_BCMA
	if (bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA) {
		bcma_write32(bcm47xx_bus.bcma.bus.drv_mips.core,
			     BCMA_MIPS_MIPS74K_INTMASK(5), 1 << 31);
		/*
		 * the kernel reads the timer irq from some register and thinks
		 * it's #5, but we offset it by 2 and route to #7
		 */
		cp0_compare_irq = 7;
	}
#endif
	mips_cpu_irq_init();
}
