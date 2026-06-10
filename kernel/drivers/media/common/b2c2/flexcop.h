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
#ifndef __FLEXCOP_H__
#define __FLEXCOP_H___

#define FC_LOG_PREFIX "b2c2-flexcop"
#include "flexcop-common.h"

extern int b2c2_flexcop_debug;

/* debug */
#ifdef CONFIG_DVB_B2C2_FLEXCOP_DEBUG
#define dprintk(level,args...) \
	do { if ((b2c2_flexcop_debug & level)) printk(args); } while (0)
#else
#define dprintk(level,args...)
#endif

#define deb_info(args...) dprintk(0x01, args)
#define deb_tuner(args...) dprintk(0x02, args)
#define deb_i2c(args...) dprintk(0x04, args)
#define deb_ts(args...) dprintk(0x08, args)
#define deb_sram(args...) dprintk(0x10, args)
#define deb_rdump(args...) dprintk(0x20, args)

#endif
