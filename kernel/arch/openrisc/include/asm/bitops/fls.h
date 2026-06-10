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
#ifndef __ASM_OPENRISC_FLS_H
#define __ASM_OPENRISC_FLS_H


#ifdef CONFIG_OPENRISC_HAVE_INST_FL1

static inline int fls(int x)
{
	int ret;

	__asm__ ("l.fl1 %0,%1"
		 : "=r" (ret)
		 : "r" (x));

	return ret;
}

#else
#include <asm-generic/bitops/fls.h>
#endif

#endif /* __ASM_OPENRISC_FLS_H */
