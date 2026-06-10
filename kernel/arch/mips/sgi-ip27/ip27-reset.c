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
#include <beep/sched.h>
#include <beep/timer.h>
#include <beep/smp.h>
#include <beep/mmzone.h>
#include <beep/nodemask.h>
#include <beep/pm.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/reboot.h>
#include <asm/sgialib.h>
#include <asm/sn/addrs.h>
#include <asm/sn/arch.h>
#include <asm/sn/gda.h>
#include <asm/sn/sn0/hub.h>

void machine_restart(char *command) __attribute__((noreturn));
void machine_halt(void) __attribute__((noreturn));
void machine_power_off(void) __attribute__((noreturn));

#define noreturn while(1);				/* Silence gcc.  */

/* XXX How to pass the reboot command to the firmware??? */
static void ip27_machine_restart(char *command)
{
#if 0
	int i;
#endif

	printk("Reboot started from CPU %d\n", smp_processor_id());
#ifdef CONFIG_SMP
	smp_send_stop();
#endif
#if 0
	for_each_online_node(i)
		REMOTE_HUB_S(COMPACT_TO_NASID_NODEID(i), PROMOP_REG,
							PROMOP_REBOOT);
#else
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
#endif
	noreturn;
}

static void ip27_machine_halt(void)
{
	int i;

#ifdef CONFIG_SMP
	smp_send_stop();
#endif
	for_each_online_node(i)
		REMOTE_HUB_S(COMPACT_TO_NASID_NODEID(i), PROMOP_REG,
							PROMOP_RESTART);
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
	noreturn;
}

static void ip27_machine_power_off(void)
{
	/* To do ...  */
	noreturn;
}

void ip27_reboot_setup(void)
{
	_machine_restart = ip27_machine_restart;
	_machine_halt = ip27_machine_halt;
	pm_power_off = ip27_machine_power_off;
}
