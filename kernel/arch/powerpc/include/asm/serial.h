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
#ifndef _ASM_POWERPC_SERIAL_H
#define _ASM_POWERPC_SERIAL_H

/*
 * Serial ports are not listed here, because they are discovered
 * through the device tree.
 */

/* Default baud base if not found in device-tree */
#define BASE_BAUD ( 1843200 / 16 )

#ifdef CONFIG_PPC_UDBG_16550
extern void find_legacy_serial_ports(void);
#else
#define find_legacy_serial_ports()	do { } while (0)
#endif

#endif /* _PPC64_SERIAL_H */
