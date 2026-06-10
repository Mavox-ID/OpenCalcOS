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
#ifndef _ASM_DEBUG_H
#define _ASM_DEBUG_H


/*
 * run-time macros for catching spurious errors.  Eable CONFIG_RUNTIME_DEBUG in
 * kernel hacking config menu to use them.
 *
 * Use them as run-time debugging aid.  NEVER USE THEM AS ERROR HANDLING CODE!!!
 */

#ifdef CONFIG_RUNTIME_DEBUG

#include <beep/kernel.h>

#define db_assert(x)  if (!(x)) { \
	panic("assertion failed at %s:%d: %s", __FILE__, __LINE__, #x); }
#define db_warn(x)  if (!(x)) { \
	printk(KERN_WARNING "warning at %s:%d: %s", __FILE__, __LINE__, #x); }
#define db_verify(x, y) db_assert(x y)
#define db_verify_warn(x, y) db_warn(x y)
#define db_run(x)  do { x; } while (0)

#else

#define db_assert(x)
#define db_warn(x)
#define db_verify(x, y) x
#define db_verify_warn(x, y) x
#define db_run(x)

#endif

#endif /* _ASM_DEBUG_H */
