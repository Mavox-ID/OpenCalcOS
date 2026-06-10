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
#include <beep/stddef.h>
#include <beep/reboot.h>
#include <beep/smp.h>
#include <beep/pm.h>
#include <asm/page.h>
#include <asm/setup.h>
#include <hv/hypervisor.h>

#ifndef CONFIG_SMP
#define smp_send_stop()
#endif

void machine_halt(void)
{
	warn_early_printk();
	arch_local_irq_disable_all();
	smp_send_stop();
	hv_halt();
}

void machine_power_off(void)
{
	warn_early_printk();
	arch_local_irq_disable_all();
	smp_send_stop();
	hv_power_off();
}

void machine_restart(char *cmd)
{
	arch_local_irq_disable_all();
	smp_send_stop();
	hv_restart((HV_VirtAddr) "vmbeep", (HV_VirtAddr) cmd);
}

/* No interesting distinction to be made here. */
void (*pm_power_off)(void) = NULL;
