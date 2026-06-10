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
#ifndef __ASM_ARCH_MXC_BOARD_MX31MOBOARD_H__
#define __ASM_ARCH_MXC_BOARD_MX31MOBOARD_H__

#ifndef __ASSEMBLY__

enum mx31moboard_boards {
	MX31NOBOARD	= 0,
	MX31DEVBOARD	= 1,
	MX31MARXBOT	= 2,
	MX31SMARTBOT	= 3,
	MX31EYEBOT	= 4,
};

/*
 * This CPU module needs a baseboard to work. After basic initializing
 * its own devices, it calls the baseboard's init function.
 */

extern void mx31moboard_devboard_init(void);
extern void mx31moboard_marxbot_init(void);
extern void mx31moboard_smartbot_init(int board);

#endif

#endif /* __ASM_ARCH_MXC_BOARD_MX31MOBOARD_H__ */
