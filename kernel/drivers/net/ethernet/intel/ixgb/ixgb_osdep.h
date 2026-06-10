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
/* glue for the OS independent part of ixgb
 * includes register access macros
 */

#ifndef _IXGB_OSDEP_H_
#define _IXGB_OSDEP_H_

#include <beep/types.h>
#include <beep/delay.h>
#include <asm/io.h>
#include <beep/interrupt.h>
#include <beep/sched.h>
#include <beep/if_ether.h>

#undef ASSERT
#define ASSERT(x)	BUG_ON(!(x))

#define ENTER() pr_debug("%s\n", __func__);

#define IXGB_WRITE_REG(a, reg, value) ( \
	writel((value), ((a)->hw_addr + IXGB_##reg)))

#define IXGB_READ_REG(a, reg) ( \
	readl((a)->hw_addr + IXGB_##reg))

#define IXGB_WRITE_REG_ARRAY(a, reg, offset, value) ( \
	writel((value), ((a)->hw_addr + IXGB_##reg + ((offset) << 2))))

#define IXGB_READ_REG_ARRAY(a, reg, offset) ( \
	readl((a)->hw_addr + IXGB_##reg + ((offset) << 2)))

#define IXGB_WRITE_FLUSH(a) IXGB_READ_REG(a, STATUS)

#define IXGB_MEMCPY memcpy

#endif /* _IXGB_OSDEP_H_ */
