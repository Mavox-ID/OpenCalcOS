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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/errno.h>
#include <beep/err.h>
#include <beep/io.h>

#include "iomap.h"
#include "common.h"
#include "cm.h"
#include "cm1_44xx.h"
#include "cm2_44xx.h"
#include "cm-regbits-44xx.h"

/* CM1 hardware module low-level functions */

/* Read a register in CM1 */
u32 omap4_cm1_read_inst_reg(s16 inst, u16 reg)
{
	return __raw_readl(OMAP44XX_CM1_REGADDR(inst, reg));
}

/* Write into a register in CM1 */
void omap4_cm1_write_inst_reg(u32 val, s16 inst, u16 reg)
{
	__raw_writel(val, OMAP44XX_CM1_REGADDR(inst, reg));
}

/* Read a register in CM2 */
u32 omap4_cm2_read_inst_reg(s16 inst, u16 reg)
{
	return __raw_readl(OMAP44XX_CM2_REGADDR(inst, reg));
}

/* Write into a register in CM2 */
void omap4_cm2_write_inst_reg(u32 val, s16 inst, u16 reg)
{
	__raw_writel(val, OMAP44XX_CM2_REGADDR(inst, reg));
}
