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
#ifndef _ASM_TILE_CURRENT_H
#define _ASM_TILE_CURRENT_H

#include <beep/thread_info.h>

struct task_struct;

static inline struct task_struct *get_current(void)
{
	return current_thread_info()->task;
}
#define current get_current()

/* Return a usable "task_struct" pointer even if the real one is corrupt. */
struct task_struct *validate_current(void);

#endif /* _ASM_TILE_CURRENT_H */
