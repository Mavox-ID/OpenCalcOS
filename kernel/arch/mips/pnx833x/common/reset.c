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
#include <beep/reboot.h>
#include <pnx833x.h>

void pnx833x_machine_restart(char *command)
{
	PNX833X_RESET_CONTROL_2 = 0;
	PNX833X_RESET_CONTROL = 0;
}

void pnx833x_machine_halt(void)
{
	while (1)
		__asm__ __volatile__ ("wait");

}

void pnx833x_machine_power_off(void)
{
	pnx833x_machine_halt();
}
