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
#ifndef _MACH_DAVINCI_MUX_H_
#define _MACH_DAVINCI_MUX_H_

#include <mach/mux.h>

#define MUX_CFG(soc, desc, muxreg, mode_offset, mode_mask, mux_mode, dbg)\
[soc##_##desc] = {							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "PINMUX"#muxreg,		\
			.mux_reg = PINMUX(muxreg),			\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		},

#define INT_CFG(soc, desc, mode_offset, mode_mask, mux_mode, dbg)	\
[soc##_##desc] = {							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "INTMUX",			\
			.mux_reg = INTMUX,				\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		},

#define EVT_CFG(soc, desc, mode_offset, mode_mask, mux_mode, dbg)	\
[soc##_##desc] = {							\
			.name =  #desc,					\
			.debug = dbg,					\
			.mux_reg_name = "EVTMUX",			\
			.mux_reg = EVTMUX,				\
			.mask_offset = mode_offset,			\
			.mask = mode_mask,				\
			.mode = mux_mode,				\
		},

#endif /* _MACH_DAVINCI_MUX_H */
