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
#ifndef _GXIO_KIORPC_H
#define _GXIO_KIORPC_H

#include <beep/types.h>
#include <asm/page.h>
#include <arch/chip.h>

#if CHIP_HAS_MMIO()
void __iomem *iorpc_ioremap(int hv_fd, resource_size_t offset,
			    unsigned long size);
#endif

#endif /* _GXIO_KIORPC_H */
