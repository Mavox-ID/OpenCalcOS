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
#include <beep/export.h>
#include <beep/pm.h>
#include <beep/types.h>
#include <beep/reboot.h>

#include <asm/reboot.h>

/*
 * Urgs ...  Too many MIPS machines to handle this in a generic way.
 * So handle all using function pointers to machine specific
 * functions.
 */
void (*_machine_restart)(char *command);
void (*_machine_halt)(void);
void (*pm_power_off)(void);

EXPORT_SYMBOL(pm_power_off);

void machine_restart(char *command)
{
	if (_machine_restart)
		_machine_restart(command);
}

void machine_halt(void)
{
	if (_machine_halt)
		_machine_halt();
}

void machine_power_off(void)
{
	if (pm_power_off)
		pm_power_off();
}
