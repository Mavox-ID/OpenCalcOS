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
/*
 *  The kernel pulls this unistd.h in three different ways:
 *  1.  the "normal" way which gets all the __NR defines
 *  2.  with __SYSCALL defined to produce function declarations
 *  3.  with __SYSCALL defined to produce syscall table initialization
 *  See also:  syscalltab.c
 */

#define sys_mmap2 sys_mmap_pgoff
#define __ARCH_WANT_SYS_CLONE

#include <asm-generic/unistd.h>
