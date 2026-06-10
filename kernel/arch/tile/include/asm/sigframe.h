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
#ifndef _ASM_TILE_SIGFRAME_H
#define _ASM_TILE_SIGFRAME_H

/* Indicate that syscall return should not examine r0 */
#define INT_SWINT_1_SIGRETURN (~0)

#ifndef __ASSEMBLY__

#include <arch/abi.h>

struct rt_sigframe {
	unsigned char save_area[C_ABI_SAVE_AREA_SIZE]; /* caller save area */
	struct siginfo info;
	struct ucontext uc;
};

#endif /* !__ASSEMBLY__ */

#endif /* _ASM_TILE_SIGFRAME_H */
