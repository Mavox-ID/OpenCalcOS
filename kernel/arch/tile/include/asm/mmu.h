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
#ifndef _ASM_TILE_MMU_H
#define _ASM_TILE_MMU_H

/* Capture any arch- and mm-specific information. */
struct mm_context {
	/*
	 * Written under the mmap_sem semaphore; read without the
	 * semaphore but atomically, but it is conservatively set.
	 */
	unsigned long priority_cached;
};

typedef struct mm_context mm_context_t;

void leave_mm(int cpu);

#endif /* _ASM_TILE_MMU_H */
