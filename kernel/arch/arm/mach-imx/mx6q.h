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
#ifndef __MACH_MX6Q_H__
#define __MACH_MX6Q_H__

#define MX6Q_IO_P2V(x)			IMX_IO_P2V(x)
#define MX6Q_IO_ADDRESS(x)		IOMEM(MX6Q_IO_P2V(x))

/*
 * The following are the blocks that need to be statically mapped.
 * For other blocks, the base address really should be retrieved from
 * device tree.
 */
#define MX6Q_SCU_BASE_ADDR		0x00a00000
#define MX6Q_SCU_SIZE			0x1000
#define MX6Q_CCM_BASE_ADDR		0x020c4000
#define MX6Q_CCM_SIZE			0x4000
#define MX6Q_ANATOP_BASE_ADDR		0x020c8000
#define MX6Q_ANATOP_SIZE		0x1000

#endif	/* __MACH_MX6Q_H__ */
