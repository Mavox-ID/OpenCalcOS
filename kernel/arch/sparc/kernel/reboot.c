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
#include <beep/reboot.h>
#include <beep/export.h>
#include <beep/pm.h>

#include <asm/oplib.h>
#include <asm/prom.h>
#include <asm/setup.h>

/* sysctl - toggle power-off restriction for serial console
 * systems in machine_power_off()
 */
int scons_pwroff = 1;

/* This isn't actually used, it exists merely to satisfy the
 * reference in kernel/sys.c
 */
void (*pm_power_off)(void) = machine_power_off;
EXPORT_SYMBOL(pm_power_off);

void machine_power_off(void)
{
	if (strcmp(of_console_device->type, "serial") || scons_pwroff)
		prom_halt_power_off();

	prom_halt();
}

void machine_halt(void)
{
	prom_halt();
	panic("Halt failed!");
}

void machine_restart(char *cmd)
{
	char *p;

	p = strchr(reboot_command, '\n');
	if (p)
		*p = 0;
	if (cmd)
		prom_reboot(cmd);
	if (*reboot_command)
		prom_reboot(reboot_command);
	prom_reboot("");
	panic("Reboot failed!");
}

