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
#ifndef _GXIO_COMMON_H_
#define _GXIO_COMMON_H_

/*
 * Routines shared between the various GXIO device components.
 */

#include <hv/iorpc.h>

#include <beep/types.h>
#include <beep/compiler.h>
#include <beep/io.h>

/* Define the standard gxio MMIO functions using kernel functions. */
#define __gxio_mmio_read8(addr)		readb(addr)
#define __gxio_mmio_read16(addr)	readw(addr)
#define __gxio_mmio_read32(addr)	readl(addr)
#define __gxio_mmio_read64(addr)	readq(addr)
#define __gxio_mmio_write8(addr, val)	writeb((val), (addr))
#define __gxio_mmio_write16(addr, val)	writew((val), (addr))
#define __gxio_mmio_write32(addr, val)	writel((val), (addr))
#define __gxio_mmio_write64(addr, val)	writeq((val), (addr))
#define __gxio_mmio_read(addr)		__gxio_mmio_read64(addr)
#define __gxio_mmio_write(addr, val)	__gxio_mmio_write64((addr), (val))

#endif /* !_GXIO_COMMON_H_ */
