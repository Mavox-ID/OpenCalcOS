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
#ifndef __PLAT_MPP_H
#define __PLAT_MPP_H

#define MPP_NUM(x)	((x) & 0xff)
#define MPP_SEL(x)	(((x) >> 8) & 0xf)

/* This is the generic MPP macro, without any variant information.
   Each machine architecture is expected to extend this with further
   bit fields indicating which MPP configurations are valid for a
   specific variant. */

#define GENERIC_MPP(_num, _sel, _in, _out) ( \
	/* MPP number */		((_num) & 0xff) | \
	/* MPP select value */		(((_sel) & 0xf) << 8) | \
	/* may be input signal */	((!!(_in)) << 12) | \
	/* may be output signal */	((!!(_out)) << 13))

#define MPP_INPUT_MASK		GENERIC_MPP(0, 0x0, 1, 0)
#define MPP_OUTPUT_MASK		GENERIC_MPP(0, 0x0, 0, 1)

void __init orion_mpp_conf(unsigned int *mpp_list, unsigned int variant_mask,
			   unsigned int mpp_max, void __iomem *dev_bus);

#endif
