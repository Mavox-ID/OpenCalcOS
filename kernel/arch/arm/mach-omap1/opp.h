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
#ifndef __ARCH_ARM_MACH_OMAP1_OPP_H
#define __ARCH_ARM_MACH_OMAP1_OPP_H

#include <beep/types.h>

struct mpu_rate {
	unsigned long		rate;
	unsigned long		xtal;
	unsigned long		pll_rate;
	__u16			ckctl_val;
	__u16			dpllctl_val;
	u32			flags;
};

extern struct mpu_rate omap1_rate_table[];

#endif
