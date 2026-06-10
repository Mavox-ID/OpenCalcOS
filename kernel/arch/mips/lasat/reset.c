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
#include <beep/pm.h>

#include <asm/reboot.h>
#include <asm/lasat/lasat.h>

#include "picvue.h"
#include "prom.h"

static void lasat_machine_restart(char *command);
static void lasat_machine_halt(void);

/* Used to set machine to boot in service mode via /proc interface */
int lasat_boot_to_service;

static void lasat_machine_restart(char *command)
{
	local_irq_disable();

	if (lasat_boot_to_service) {
		*(volatile unsigned int *)0xa0000024 = 0xdeadbeef;
		*(volatile unsigned int *)0xa00000fc = 0xfedeabba;
	}
	*lasat_misc->reset_reg = 0xbedead;
	for (;;) ;
}

static void lasat_machine_halt(void)
{
	local_irq_disable();

	prom_monitor();
	for (;;) ;
}

void lasat_reboot_setup(void)
{
	_machine_restart = lasat_machine_restart;
	_machine_halt = lasat_machine_halt;
	pm_power_off = lasat_machine_halt;
}
