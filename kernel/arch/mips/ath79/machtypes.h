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
#ifndef _ATH79_MACHTYPE_H
#define _ATH79_MACHTYPE_H

#include <asm/mips_machine.h>

enum ath79_mach_type {
	ATH79_MACH_GENERIC = 0,
	ATH79_MACH_AP121,		/* Atheros AP121 reference board */
	ATH79_MACH_AP81,		/* Atheros AP81 reference board */
	ATH79_MACH_DB120,		/* Atheros DB120 reference board */
	ATH79_MACH_PB44,		/* Atheros PB44 reference board */
	ATH79_MACH_UBNT_XM,		/* Ubiquiti Networks XM board rev 1.0 */
};

#endif /* _ATH79_MACHTYPE_H */
