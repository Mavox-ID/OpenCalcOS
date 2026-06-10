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
#ifndef CORE_H
#define CORE_H

/* Physical addresses/sizes */
#define ISAMEM_PHYS		0xe0000000
#define ISAMEM_SIZE		0x10000000

#define ISAIO_PHYS		0xf0000000
#define ISAIO_SIZE		PGDIR_SIZE

#define TRICK0_PHYS		0xf2000000
#define TRICK0_SIZE		PGDIR_SIZE
#define TRICK1_PHYS		0xf2400000
#define TRICK1_SIZE		PGDIR_SIZE
#define TRICK2_PHYS		0xf2800000
#define TRICK3_PHYS		0xf2c00000
#define TRICK3_SIZE		PGDIR_SIZE
#define TRICK4_PHYS		0xf3000000
#define TRICK4_SIZE		PGDIR_SIZE
#define TRICK5_PHYS		0xf3400000
#define TRICK6_PHYS		0xf3800000
#define TRICK7_PHYS		0xf3c00000

/* Virtual addresses */
#define PIT_BASE		IOMEM(0xfc000000)	/* trick 0 */
#define SOFT_BASE		IOMEM(0xfd000000)	/* trick 1 */
#define IRQ_MASK		IOMEM(0xfe000000)	/* trick 3 - read */
#define IRQ_MSET		IOMEM(0xfe000000)	/* trick 3 - write */
#define IRQ_STAT		IOMEM(0xff000000)	/* trick 4 - read */
#define IRQ_MCLR		IOMEM(0xff000000)	/* trick 4 - write */

#endif
