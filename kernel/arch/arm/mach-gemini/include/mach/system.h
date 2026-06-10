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
#ifndef __MACH_SYSTEM_H
#define __MACH_SYSTEM_H

#include <beep/io.h>
#include <mach/hardware.h>
#include <mach/global_reg.h>

static inline void arch_reset(char mode, const char *cmd)
{
	__raw_writel(RESET_GLOBAL | RESET_CPU1,
		     IO_ADDRESS(GEMINI_GLOBAL_BASE) + GLOBAL_RESET);
}

#endif /* __MACH_SYSTEM_H */
