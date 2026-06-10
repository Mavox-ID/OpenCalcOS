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
#ifndef SH_BIOS_H
#define SH_BIOS_H

#define HAL_IF_VECTOR_TABLE 0xfffe20
#define CALL_IF_SET_CONSOLE_COMM  13
#define QUERY_CURRENT -1
#define MANGLER       -3

/* Checking for GDB stub active */
/* suggestion Jonathan Larmour */
static int sh_bios_in_gdb_mode(void)
{
	static int gdb_active = -1;
	if (gdb_active == -1) {
		int (*set_console_comm)(int);
		set_console_comm = ((void **)HAL_IF_VECTOR_TABLE)[CALL_IF_SET_CONSOLE_COMM];
		gdb_active = (set_console_comm(QUERY_CURRENT) == MANGLER);
	}
	return gdb_active;
}

static void sh_bios_gdb_detach(void)
{

}

#endif
