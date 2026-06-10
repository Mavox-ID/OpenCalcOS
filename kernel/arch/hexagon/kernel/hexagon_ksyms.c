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
#include <asm/hexagon_vm.h>
#include <asm/uaccess.h>

EXPORT_SYMBOL(__copy_from_user_hexagon);
EXPORT_SYMBOL(__copy_to_user_hexagon);
EXPORT_SYMBOL(__vmgetie);
EXPORT_SYMBOL(__vmsetie);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(memset);

#define DECLARE_EXPORT(name)     \
	extern void name(void); EXPORT_SYMBOL(name)

/* Symbols found in libgcc that assorted kernel modules need */
DECLARE_EXPORT(__hexagon_memcpy_likely_aligned_min32bytes_mult8bytes);

DECLARE_EXPORT(__hexagon_divsi3);
DECLARE_EXPORT(__hexagon_modsi3);
DECLARE_EXPORT(__hexagon_udivsi3);
DECLARE_EXPORT(__hexagon_umodsi3);
