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
#ifndef __ASM_ARCH_GPIO_H
#define __ASM_ARCH_GPIO_H

#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/io.h>

/*
 * FIXME !!
 *
 * current gpio frame work doesn't have
 * the method to control only pull up/down/free.
 * this function should be replaced by correct gpio function
 */
static inline void __init gpio_direction_none(void __iomem * addr)
{
	__raw_writeb(0x00, addr);
}

static inline void __init gpio_request_pullup(void __iomem * addr)
{
	u8 data = __raw_readb(addr);

	data &= 0x0F;
	data |= 0xC0;
	__raw_writeb(data, addr);
}

static inline void __init gpio_request_pulldown(void __iomem * addr)
{
	u8 data = __raw_readb(addr);

	data &= 0x0F;
	data |= 0xA0;

	__raw_writeb(data, addr);
}

#endif /* __ASM_ARCH_GPIO_H */
