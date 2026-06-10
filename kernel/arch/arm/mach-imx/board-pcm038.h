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
#ifndef __ASM_ARCH_MXC_BOARD_PCM038_H__
#define __ASM_ARCH_MXC_BOARD_PCM038_H__

#ifndef __ASSEMBLY__
/*
 * This CPU module needs a baseboard to work. After basic initializing
 * its own devices, it calls the baseboard's init function.
 * TODO: Add your own baseboard init function and call it from
 * inside pcm038_init().
 *
 * This example here is for the development board. Refer pcm970-baseboard.c
 */

extern void pcm970_baseboard_init(void);

#endif

#endif /* __ASM_ARCH_MXC_BOARD_PCM038_H__ */
