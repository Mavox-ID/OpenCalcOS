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
#ifndef _ASM_SH_IO_SH03_H
#define _ASM_SH_IO_SH03_H

#include <beep/time.h>

#define IRL0_IRQ	2
#define IRL0_PRIORITY	13
#define IRL1_IRQ	5
#define IRL1_PRIORITY	10
#define IRL2_IRQ	8
#define IRL2_PRIORITY	7
#define IRL3_IRQ	11
#define IRL3_PRIORITY	4

void heartbeat_sh03(void);

#endif /* _ASM_SH_IO_SH03_H */
