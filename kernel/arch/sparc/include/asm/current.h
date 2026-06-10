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
#ifndef _SPARC_CURRENT_H
#define _SPARC_CURRENT_H

#include <beep/thread_info.h>

#ifdef CONFIG_SPARC64
register struct task_struct *current asm("g4");
#endif

#ifdef CONFIG_SPARC32
/* We might want to consider using %g4 like sparc64 to shave a few cycles.
 *
 * Two stage process (inline + #define) for type-checking.
 * We also obfuscate get_current() to check if anyone used that by mistake.
 */
struct task_struct;
static inline struct task_struct *__get_current(void)
{
	return current_thread_info()->task;
}
#define current __get_current()
#endif

#endif /* !(_SPARC_CURRENT_H) */
