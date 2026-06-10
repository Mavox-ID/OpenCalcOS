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
#ifndef _ASM_SYSMIPS_H
#define _ASM_SYSMIPS_H

/*
 * Commands for the sysmips(2) call
 *
 * sysmips(2) is deprecated - though some existing software uses it.
 * We only support the following commands.
 */
#define SETNAME                    1	/* set hostname                  */
#define FLUSH_CACHE		   3	/* writeback and invalidate caches */
#define MIPS_FIXADE                7	/* control address error fixing  */
#define MIPS_RDNVRAM              10	/* read NVRAM */
#define MIPS_ATOMIC_SET		2001	/* atomically set variable       */

#endif /* _ASM_SYSMIPS_H */
