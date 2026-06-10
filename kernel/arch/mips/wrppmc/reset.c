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
#include <beep/irqflags.h>
#include <beep/kernel.h>

#include <asm/cacheflush.h>
#include <asm/mipsregs.h>
#include <asm/processor.h>

void wrppmc_machine_restart(char *command)
{
	/*
	 * Ouch, we're still alive ... This time we take the silver bullet ...
	 * ... and find that we leave the hardware in a state in which the
	 * kernel in the flush locks up somewhen during of after the PCI
	 * detection stuff.
	 */
	local_irq_disable();
	set_c0_status(ST0_BEV | ST0_ERL);
	change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
	flush_cache_all();
	write_c0_wired(0);
	__asm__ __volatile__("jr\t%0"::"r"(0xbfc00000));
}

void wrppmc_machine_halt(void)
{
	local_irq_disable();

	printk(KERN_NOTICE "You can safely turn off the power\n");
	while (1) {
		if (cpu_wait)
			cpu_wait();
	}
}
